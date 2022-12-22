#pragma once

#include <cstdint>
#include <vector>
#include <map>
#include <string>

#include "http.hpp"
#include "stream.hpp"
#include "error.hpp"

namespace edjx {

/// APIs for executing HTTP requests.
namespace fetch {

    /**
     * @brief Response for HTTP fetch request, which may include body,
     * headers, and status code.
     */
    struct FetchResponse {
        /// HTTP status code of the response
        edjx::http::HttpStatusCode status;
        /// HTTP headers of the response
        edjx::http::HttpHeaders headers;
        /// Body of the response as a stream
        edjx::stream::ReadStream read_stream;

        /**
         * @brief Returns the HTTP status code of the fetch response.
         * 
         * @return Response status code
         */
        edjx::http::HttpStatusCode get_status_code() const;

        /**
         * @brief Returns HTTP headers of the fetch response.
         * 
         * @return HTTP headers
         */
        const edjx::http::HttpHeaders & get_headers() const;

        /**
         * @brief Reads and returns the HTTP body of the fetch response.
         * 
         * This method should not be called more than once.
         * 
         * @param result Response body will be copied to this object.
         * @return Returns edjx::error::StreamError::Success on success,
         * edjx::error::StreamError::EndOfStream when end of stream is reached,
         * or some other value on failure. 
         */
        edjx::error::StreamError read_body(std::vector<uint8_t> & result);

        /**
         * @brief Returns the HTTP body of the fetch response as a read stream.
         * 
         * @return Response body as a stream.
         */
        edjx::stream::ReadStream & get_read_stream();
    };

    /**
     * @brief A pending Fetch response.
     * 
     * This struct is used as a placeholder for a response
     * from the server during Fetch request streaming,
     * before an actual server response is received.
     * 
     * Once a response is received from the server, it can
     * be retrieved via the get_fetch_response() method.
     */
    struct FetchResponsePending {
        /// Stream descriptor
        uint32_t sd;

        FetchResponsePending() {}
        FetchResponsePending(uint32_t sd) : sd(sd) {}

        /**
         * @brief Get the server's response
         * 
         * @param result Server's response will be copied to this object.
         * @return Returns edjx::error::HttpError::Success on success,
         * some other value on failure.
         */
        edjx::error::HttpError get_fetch_response(FetchResponse & result);
    };

    /**
     * @brief An HTTP fetch request includes body, headers,
     * version, method, and URI.
     */
    struct HttpFetch {
        /// HTTP version of the request.
        http::HttpVersion version;
        /// Headers for the request.
        edjx::http::HttpHeaders headers;
        /// URI of the request.
        http::Uri uri;
        /// Method for the request.
        http::HttpMethod method;
        /// Request body.
        std::vector<uint8_t> body;

        /**
         * @brief Creates a request with the given method and URI,
         * version as HTTP/1.1, no headers, and no body.
         * 
         * @param uri Request URI
         * @param method Request method
         */
        inline HttpFetch(http::Uri uri, http::HttpMethod method) :
            version(http::HttpVersion::HTTP_11),
            uri(uri),
            method(method) {}

        /**
         * @brief Sets the HTTP version of the request.
         * 
         * @param version Version to be set
         * @return Reference to this HttpFetch object
         */
        HttpFetch & set_version(http::HttpVersion version);

        /**
         * @brief Gets the HTTP version of the request.
         * 
         * @return HTTP version of the request
         */
        http::HttpVersion get_version() const;

        /**
         * @brief Sets a request header to the given value.
         * 
         * Discards any previous values for the given header name.
         * 
         * @param header_name Header name
         * @param value Header value
         * @return Reference to this HttpFetch object
         */
        HttpFetch & set_header(
            const std::string & header_name,
            const std::string & value
        );

        /**
         * @brief Sets a request header to the given values.
         * 
         * Discards any previous values for the given header name.
         * 
         * @param header_name Header name
         * @param value Header values
         * @return Reference to this HttpFetch object
         */
        HttpFetch & set_header(
            const std::string & header_name,
            const std::vector<std::string> & value
        );

        /**
         * @brief Appends a value to the existing request header.
         * 
         * Keeps any previous values for the given header name.
         * 
         * @param header_name Header name
         * @param value Header value
         * @return Reference to this HttpFetch object
         */
        HttpFetch & append_header(
            const std::string & header_name,
            const std::string & value
        );

        /**
         * @brief Set request headers to the given values.
         * 
         * All previously defined headers will be discarded.
         * 
         * @param value HTTP headers
         * @return Reference to this HttpFetch object
         */
        HttpFetch & set_headers(
            const edjx::http::HttpHeaders & value
        );

        /**
         * @brief Returns a const reference to the request header map
         * 
         * @return Request headers
         */
        const edjx::http::HttpHeaders & get_headers() const;

        /**
         * @brief Sets the given [`text`] value as the body of the request.
         * 
         * Any body that was previously set on the request is discarded.
         * 
         * @param text String to be used as the body
         * @return Reference to this HttpFetch object
         */
        HttpFetch & set_body(const std::string & text);

        /**
         * @brief Sets the given [`bytes`] value as the body of the request.
         * 
         * Any body that was previously set on the request is discarded.
         * 
         * @param bytes Bytes to be used as the body
         * @return Reference to this HttpFetch object
         */
        HttpFetch & set_body(const std::vector<std::uint8_t> bytes);

        /**
         * @brief Returns a constant reference to the body.
         * 
         * @return Request body
         */
        const std::vector<uint8_t> & get_body() const;

        /**
         * @brief Sends the request to the server, and returns after the
         * response is received or an error occurs.
         * 
         * @param response 
         * @return Returns edjx::error::HttpError::Success on success,
         * some other value on failure.
         */
        edjx::error::HttpError send(FetchResponse & response);

        /**
         * @brief Starts streaming an HTTP Fetch request to the server.
         * This method returns a `FetchResponsePending` object and an `edjx::stream::WriteStream` object.
         * The `edjx::stream::WriteStream` object is used to stream data. The `FetchResponsePending`
         * is a placeholder to retreive `FetchResponse`. In the background,
         * this method triggers sending HTTP headers and other HTTP artifacts
         * to the server.
         * 
         * This method and the send() method cannot be used together.
         * 
         * @param response A placeholder for the server's response will
         * be copied to this object.
         * It can retreive the server's response once the response is received.
         * @param write_stream A write stream for streaming the HTTP Fetch
         * request body.
         * @return Returns edjx::error::HttpError::Success on success,
         * some other value on failure.
         */
        edjx::error::HttpError send_streaming(FetchResponsePending & response, edjx::stream::WriteStream & write_stream);
    };

}}
