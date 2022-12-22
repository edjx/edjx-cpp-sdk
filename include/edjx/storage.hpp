#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "stream.hpp"
#include "error.hpp"

namespace edjx {

// APIs for interacting with the EDJX Object Store.
namespace storage {

    /**
     * @brief Response to the [`edjx::storage::get`] request.
     */
    struct StorageResponse {
        /// HTTP headers of the response
        std::map<std::string, std::string> headers;
        /// Body of the response as a read stream
        edjx::stream::ReadStream read_stream;

        /**
         * @brief Constructs a response with no headers and an empty body.
         */
        inline StorageResponse() {}

        /**
         * @brief Constructs a response with headers and body set
         * to the provided values.
         * 
         * @param headers HTTP headers for the response
         * @param read_stream Read stream for the body of the response
         */
        inline StorageResponse(
            const std::map<std::string, std::string> & headers,
            const edjx::stream::ReadStream & read_stream
        ) : headers(headers),
            read_stream(read_stream) {}

        /**
         * @brief Returns the metadata associated with the storage object.
         * 
         * @return Response headers
         */
        const std::map<std::string, std::string> & get_headers() const;

        /**
         * @brief Retrieves the bytes of the storage object.
         * 
         * @param result Response body
         * @return Returns StorageError::Success on success,
         * StorageError::Success::EndOfStream when end of stream is reached,
         * or some other value on failure.
         */
        edjx::error::StreamError read_body(std::vector<uint8_t> & result);

        /**
         * @brief Returns a read stream for the storage object.
         * 
         * @return Read stream
         */
        const edjx::stream::ReadStream & get_read_stream() const;
    };

    /**
     * @brief Placeholder for storage response used in streaming methods
     * when the response is not available immediately.
     */
    struct StorageResponsePending {
        /// Stream descriptor
        uint32_t sd;

        /**
         * @brief Constructs an uninitialized response holder.
         */
        StorageResponsePending() {}
        /**
         * @brief Constructs a response holder for a stream identified
         * by the stream descriptor `sd`.
         * 
         * @param sd Stream descriptor
         */
        StorageResponsePending(uint32_t sd) : sd(sd) {}

        /**
         * @brief Attempts to retrieve the storage response if it is ready.
         * 
         * @param result Retrieved storage response
         * @return Returns edjx::error::StorageError::Success on success,
         * some other value otherwise.
         */
        edjx::error::StorageError get_storage_response(StorageResponse & result);
    };

    /**
     * @brief Represents the attributes associated with a stored file.
     */
    struct FileAttributes {
        /// Whether file properties are defined
        bool properties_present;
        /// File properties
        std::map<std::string, std::string> properties;
        /// Whether default version is present
        bool default_version_present;
        /// Default version
        std::string default_version;

        /**
         * @brief Construct an empty file attributes object.
         */
        inline FileAttributes() :
            properties_present(false),
            default_version_present(false) {}

        /**
         * @brief Construct a new File Attributes object.
         * 
         * @param properties_present Whether file properties are present
         * @param properties File properties
         * @param default_version_present Whether default version is present
         * @param default_version Default version
         */
        inline FileAttributes(
            bool properties_present,
            const std::map<std::string, std::string> & properties,
            bool default_version_present,
            const std::string & default_version
        ) : properties_present(properties_present),
            properties(properties),
            default_version_present(default_version_present),
            default_version(default_version) {}
    };

    /**
     * @brief Returns a file from the EDJX Object Store.
     * 
     * @param result Result File
     * @param bucket_id Bucket ID
     * @param file_name File name
     * @return edjx::storage::StorageError::Success on success,
     * some other value on failure
     */
    edjx::error::StorageError get(
        StorageResponse & result,
        const std::string & bucket_id,
        const std::string & file_name
    );

    /**
     * @brief Uploads a file to the EDJX Object Store.
     * 
     * @param result Result of the operation
     * @param bucket_id Bucket ID
     * @param file_name File name
     * @param properties Properties
     * @param contents File content
     * @return edjx::error::StorageError::Success on success,
     * some other value on failure
     */
    edjx::error::StorageError put(
        StorageResponse & result,
        const std::string & bucket_id,
        const std::string & file_name,
        const std::string & properties,
        const std::vector<uint8_t> contents
    );

    /**
     * @brief Starts streaming a file to the EDJX Object Store.
     * 
     * This method returns two objects, an edjx::stream::WriteStream and
     * a StorageResponsePending.
     * The edjx::stream::WriteStream is used to stream data, and the
     * StorageResponsePending is a placeholder to retreive the
     * StorageResponse response from the storage.
     * 
     * @param response_streaming If successful, this method will populate
     * this argument with a placeholder for the storage response.
     * @param write_stream If successful, this method will populate this
     * argument with a write stream to be used for streaming the data.
     * @param bucket_id Bucket ID (where to put the file)
     * @param file_name File name
     * @param properties Properties of the file
     * @return Returns edjx::error::StorageError::Success on success,
     * some other value on failure
     */
    edjx::error::StorageError put_streaming(
        StorageResponsePending & response_streaming,
        edjx::stream::WriteStream & write_stream,
        const std::string & bucket_id,
        const std::string & file_name,
        const std::string & properties
    );

    /**
     * @brief Deletes the given file from the EDJX Object Store.
     * 
     * @param result Result of the operation
     * @param bucket_id Bucket ID
     * @param file_name File Name
     * @return edjx::error::StorageError::Success on success,
     * some other value on failure
     */
    edjx::error::StorageError remove(
        StorageResponse result,
        const std::string & bucket_id,
        const std::string & file_name
    );

    /**
     * @brief Returns attributes associated with the given file from
     * the EDJX Object Store.
     * 
     * @param result Result of the operation
     * @param bucket_id Bucket ID
     * @param file_name File name
     * @return edjx::error::StorageError::Success on success,
     * some other value on failure
     */
    edjx::error::StorageError get_attributes(
        FileAttributes & result,
        const std::string & bucket_id,
        const std::string & file_name
    );

    /**
     * @brief Sets the attributes associated with the given file.
     * 
     * This setting replaces the existing attributes.
     * 
     * @param result Result of the operation
     * @param bucket_id Bucket ID
     * @param file_name File name
     * @param attributes File attributes
     * @return edjx::error::StorageError::Success on success,
     * some other value on failure
     */
    edjx::error::StorageError set_attributes(
        StorageResponse & result,
        const std::string & bucket_id,
        const std::string & file_name,
        const FileAttributes & attributes
    );

}}
