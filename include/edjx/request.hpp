#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <map>

#include "http.hpp"
#include "stream.hpp"
#include "error.hpp"

namespace edjx {

/**
 * @brief Read-only HTTP request input for HTTP-trigger serverless functions.
 * 
 * For executing HTTP Requests, use [`edjx::fetch::HttpFetch`].
 */
namespace request {

    /**
     * @brief Request, which may include version, body, headers,
     * method, and URL.
     */
    struct HttpRequest {
        /// Whether this object has been initialized or not
        bool initialized;
        /// HTTP version of the request
        http::HttpVersion version;
        /// HTTP method of the request
        http::HttpMethod method;
        /// URL of the request
        http::Uri uri;
        /// HTTP headers of the request
        edjx::http::HttpHeaders headers;

        /**
         * @brief Creates an empty request object with HTTP version set
         * to HTTP/1.1, HTTP method of NONE, and no body.
         */
        HttpRequest()
            : initialized(false),
            version(http::HttpVersion::HTTP_11),
            method(http::HttpMethod::NONE) {}


        /**
         * @brief Returns the client request being handled by the
         * serverless function.
         * 
         * Normally, this method does not need to be used explicitly.
         * EDJX sample [`C++ Serverless Application`]
         * (https://github.com/edjx/edjfunction-example-cpp) code file
         * (main.cpp) uses this method to fetch HTTP Request.
         * 
         * @param result HttpRequest in which the request will be stored
         * @return Returns edjx::error::HttpError::Success on success,
         * some other value if execution failed.
         */
        static edjx::error::HttpError from_client(HttpRequest & result);

        /**
         * @brief Returns the HTTP method of the request.
         * 
         * @return HTTP method of the request
         */
        http::HttpMethod get_method() const;

        /**
         * @brief Returns the URL from the request.
         * 
         * Returns the request URL value as [`edjx::http::Uri`] object.
         * 
         * @return URL of the request
         */
        http::Uri get_uri() const;

        /**
         * @brief Returns HTTP headers of the request.
         * 
         * Returns the map of headers in the request as a map of header names
         * to a vector of header values.
         * 
         * @return Request headers
         */
        const edjx::http::HttpHeaders & get_headers() const;

        /**
         * @brief Fetches the request body and returns the body as bytes.
         * 
         * @param result Received body bytes will be stored here.
         * @return Returns edjx::error::HttpError::Success on success,
         * some other value on failure.
         */
        edjx::error::HttpError read_body(std::vector<uint8_t> & result);

        /**
         * @brief Opens a read stream to read the request body.
         * 
         * `read_body()` and `open_read_stream()` cannot be used at the same time.
         * 
         * @param result HTTP request body read stream
         * @return Returns edjx::error::HttpError::Success on success,
         * some other value on failure.
         */
        edjx::error::HttpError open_read_stream(edjx::stream::ReadStream & result);
    };

}}