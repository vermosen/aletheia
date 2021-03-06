/*
 * ssl.cpp
 *
 *  Created on: May 25, 2016
 *      Author: vermosen
 */

#include <connectors/ssl.hpp>

namespace connectors {

	ssl::ssl(const boost::shared_ptr<logger> & l, bool verifyHost)
		: 	connector(l),
			context_(boost::asio::ssl::context::sslv23),
			resolver_(service_),
			socket_(service_, context_),
			answered_(false)
	{

		// load the certificate from default
		context_.set_default_verify_paths();

		if (verifyHost)
		{
			// set verify mode
			socket_.set_verify_mode(boost::asio::ssl::verify_peer);

			// set the callbacks
			socket_.set_verify_callback(
				boost::bind(&ssl::handle_checkCertificate, this, _1, _2));
		}
		else
		{
			socket_.set_verify_mode(boost::asio::ssl::verify_none);
		}
	}

	void ssl::setHost(const std::string & host, const std::string & port)
	{
		port_ = port; host_ = host;

		logger_->add("trying to resolve host " + host,
			logger::messageType::information,
			logger::verbosity::low);

		query_ = boost::shared_ptr<boost::asio::ip::tcp::resolver::query>(
			new boost::asio::ip::tcp::resolver::query(host_, port_));
	}

	void ssl::setQuery(const boost::shared_ptr<query> & qr)
	{

		logger_->add("setting new query...",
			logger::messageType::information,
			logger::verbosity::low);

		try
		{
			// build the query
			std::ostream request_stream(&request_);
			request_stream << "GET /";
			request_stream << qr->getStream().str();
			request_stream << " HTTP/1.1\r\n";
			request_stream << "Host: " << host_ << "\r\n";
			request_stream << "Accept: */*\r\n";
			request_stream << "Connection: close\r\n\r\n";
			ready_ = true;

			logger_->add("new query set for the distant host:\r\n" +
				std::string(buffers_begin(request_.data()),
					buffers_begin(request_.data()) + request_.size()),
					logger::messageType::information,
					logger::verbosity::medium);
		}
		catch(std::exception & ex)
		{
			logger_->add("error while creating the query",
				logger::messageType::error,
				logger::verbosity::high);

			ready_ = false;
		}
	}

	void ssl::connect()
	{
		resolver_.async_resolve(*query_,
			boost::bind(&ssl::handle_resolve, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::iterator));

		service_.run();
	}

	std::stringstream & ssl::getStream()
	{

		if (!answered_ && ready_)

		{
			boost::chrono::high_resolution_clock timer;
			boost::chrono::time_point<boost::chrono::high_resolution_clock> start = timer.now();
			boost::mutex::scoped_lock lock(ioMutex_);
			this->connect();

			// should be useless...
			while (!answered_ && boost::chrono::duration_cast<boost::chrono::milliseconds>(
					timer.now() - start).count() < TIMEOUT)
			{
				condition_.wait(lock);
			}

			if (success_)
			{
				logger_->add("query retrieved in " + boost::lexical_cast<std::string>(
					boost::chrono::duration_cast<boost::chrono::milliseconds>(
					timer.now() - start).count()) + " ms",
					logger::messageType::information,
					logger::verbosity::high);
			}
			else
			{
				logger_->add("query failed",
					logger::messageType::error,
					logger::verbosity::high);
			}
		}

		return content_;
	}

	void ssl::unckunck(boost::asio::streambuf & buf)
	{
		bool start = true;
		std::string c;

		std::istream istr(&buf);
		istr >> std::noskipws;

		while (istr)
		{
			std::string h;
			if (!start)
			{
				std::getline(istr, h);
			}
			else
			{
				start = false;
			}

			std::getline(istr, h);
			std::stringstream ss;
			ss << std::hex << h.substr(0, h.size()-1);
			ss >> chunckSize_;

			std::istream_iterator<char> beg(istr);

			std::copy_n(beg, chunckSize_, std::back_inserter(c));
		}

		content_ << c;
	}

	// callbacks
	bool ssl::handle_checkCertificate(bool preverified, boost::asio::ssl::verify_context& ctx)
	{
		char subject_name[256];
		X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
		X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);

		logger_->add("Verifying " + std::string(subject_name),
			logger::messageType::information,
			logger::verbosity::low);

		return preverified;
	}
	void ssl::handle_resolve(const boost::system::error_code& err,
						boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
	{
		if (!err)
		{
			logger_->add("host address resolved",
				logger::messageType::information,
				logger::verbosity::low);

			boost::asio::async_connect(socket_.lowest_layer(), endpoint_iterator,
				boost::bind(&ssl::handle_connect, this,
					boost::asio::placeholders::error));
		}
		else
		{
			logger_->add("Error resolving host address:\r\n" + err.message(),
				logger::messageType::error,
				logger::verbosity::high);

			condition_.notify_one(); answered_ = true;
		}
	}
	void ssl::handle_connect(const boost::system::error_code& err)
	{
		if (!err)
		{
		  socket_.async_handshake(boost::asio::ssl::stream_base::client,
			  boost::bind(&ssl::handle_handshake, this,
				boost::asio::placeholders::error));
		}
		else
		{
			logger_->add("Error connecting host:\r\n" + err.message(),
				logger::messageType::error,
				logger::verbosity::high);

			condition_.notify_one(); answered_ = true;
		}
	}
	void ssl::handle_handshake(const boost::system::error_code& err)
	{
		if (!err)
		{
			logger_->add("host successfully handchecked",
				logger::messageType::information,
				logger::verbosity::low);

			boost::asio::async_write(socket_, request_,
				boost::bind(&ssl::handle_write_request, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
		}
		else
		{
			logger_->add("Error performing handshake:\r\n" + err.message(),
				logger::messageType::error,
				logger::verbosity::high);

			condition_.notify_one(); answered_ = true;
		}
	}
	void ssl::handle_write_request(const boost::system::error_code& err, size_t bytes_transferred)
	{
		logger_->add("new write attempt",
			logger::messageType::information,
			logger::verbosity::low);

		if (!err)
		{
			logger_->add("sending new request",
				logger::messageType::information,
				logger::verbosity::low);

			boost::asio::async_read_until(socket_, response_, "\r\n",
				boost::bind(&ssl::handle_read_status_line, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
		}
		else
		{
			logger_->add("Error writing query:\r\n" + err.message(),
				logger::messageType::error,
				logger::verbosity::high);

			condition_.notify_one(); answered_ = true;
		}
	}
	void ssl::handle_read_status_line(const boost::system::error_code& err, size_t bytes_transferred)
	{
		if (!err)
		{
			// Check that the response is OK.
			std::istream response_stream(&response_);
			std::string http_version;
			response_stream >> http_version;

			unsigned int status_code;
			response_stream >> status_code;

			std::string status_message;
			std::getline(response_stream, status_message);
			if (!response_stream || http_version.substr(0, 5) != "HTTP/")
			{
				logger_->add("Invalid response\n",
					logger::messageType::error,
					logger::verbosity::high);

				condition_.notify_one(); answered_ = true;
				return;
			}
			if (status_code != 200)
			{
				logger_->add("Response returned with status code "
					+ boost::lexical_cast<std::string>(status_code) + "\r\n",
					logger::messageType::error,
					logger::verbosity::high);

				condition_.notify_one(); answered_ = true;
				return;
			}

			logger_->add("Status code: "
				+ boost::lexical_cast<std::string>(status_code) + "\r\n",
				logger::messageType::information,
				logger::verbosity::low);

			// Read the response headers, which are terminated by a blank line.
			boost::asio::async_read_until(socket_, response_, "\r\n\r\n",
				boost::bind(&ssl::handle_read_headers, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
		}
		else
		{
			logger_->add("Error: " + err.message() + "\n",
				logger::messageType::error,
				logger::verbosity::high);

			condition_.notify_one(); answered_ = true;
		}
	}
	void ssl::handle_read_headers(const boost::system::error_code& err, size_t bytes_transferred)
	{
		if (!err)
		{
			// Process the response headers.
			std::istream response_stream(&response_);

			// unload the bufstream in header_ until we reached the content (standalone empty line)
			// TODO: we may reach the end of the packet before the end of the header
			std::string h; while (std::getline(response_stream, h) && h != "\r")
			{
				// TODO: use regex for the space
				if (h.find("transfer-encoding: chunked") != std::string::npos) chunked_ = true;
				header_ << h;
			}

			// Start reading remaining data until EOF.
			boost::asio::async_read(socket_, response_,
				boost::asio::transfer_at_least(1),
				boost::bind(&ssl::handle_read_content, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
		}
		else
		{
			logger_->add("Error: " + err.message() + "\n",
				logger::messageType::error,
				logger::verbosity::high);

			condition_.notify_one(); answered_ = true;
		}
	}
	void ssl::handle_read_content(const boost::system::error_code& err, size_t bytes_transferred)
	{
		if (!err)
		{
			// Continue reading remaining data until EOF.
			boost::asio::async_read(socket_, response_,
					boost::asio::transfer_at_least(1),
				boost::bind(&ssl::handle_read_content, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));

		}
		else if (err == boost::asio::error::eof)
		{
			if (chunked_)
			{
				unckunck(response_);
			}
			else
			{
				content_ << &response_;
			}

			success_ = true;
			condition_.notify_one(); answered_ = true;
		}
		else if (err != boost::asio::error::eof)
		{
			logger_->add("Error: " + err.message() + "\n",
				logger::messageType::error,
				logger::verbosity::high);

			condition_.notify_one(); answered_ = true;
		}
	}

} /* namespace connector */
