/*
 * ssl.hpp
 *
 *  Created on: May 25, 2016
 *      Author: vermosen
 */

#ifndef CONNECTORS_SSL_HPP_
#define CONNECTORS_SSL_HPP_

#include <cstdlib>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/completion_condition.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/chrono.hpp>

#include "connector.hpp"
#include "dataFiles/json.hpp"
#include "dataFiles/csv.hpp"

#define TIMEOUT 5000

namespace connectors {

	enum { max_length = 1024 };

	class ssl : public connector
	{
	public:

		ssl(const boost::shared_ptr<logger> & l, bool verifyHost = false);

		// interfaces
		virtual void setHost(const std::string & host, int port = -1);
		virtual void setQuery(const boost::shared_ptr<query> &);
		virtual void connect();
		virtual std::stringstream & getStream();

	private:
		void unckunck(boost::asio::streambuf & buf);

		// client callbacks
		bool handle_checkCertificate(bool, boost::asio::ssl::verify_context&);
		void handle_resolve			(const boost::system::error_code&, boost::asio::ip::tcp::resolver::iterator);
		void handle_connect			(const boost::system::error_code&);
		void handle_handshake		(const boost::system::error_code&);
		void handle_write_request	(const boost::system::error_code&, size_t);
		void handle_read_status_line(const boost::system::error_code&, size_t);
		void handle_read_headers	(const boost::system::error_code&, size_t);
		void handle_read_content	(const boost::system::error_code&, size_t);

	private:
		boost::asio::io_service service_;
		boost::asio::ssl::context context_;
		boost::asio::ip::tcp::resolver resolver_;
		boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;
		boost::shared_ptr<boost::asio::ip::tcp::resolver::query> query_;

		std::string host_;
		std::string port_;


		std::stringstream content_;
		std::stringstream header_;

		boost::asio::streambuf request_;
	    boost::asio::streambuf response_;

	    bool ready_;
	    bool success_;

	    // for chucks management
	    bool chunked_;
	    int chunckSize_;

	    // for async controls
	    boost::mutex 				ioMutex_	;
	    boost::condition_variable 	condition_	;
		boost::atomic<bool> 		answered_	;


	};
} /* namespace connector */

#endif /* CONNECTORS_SSL_HPP_ */
