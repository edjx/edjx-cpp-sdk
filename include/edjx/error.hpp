#pragma once

#include "http.hpp"

namespace edjx {

/// Error-handling enums and utilities.
namespace error {

    /**
     * @brief Enum describing return values of functions that
     * correspond to HTTP modules.
     */
    enum class HttpError {
        /// Operation was successful.
        Success = 0,
        /// An error occured in the SDK library.
        SystemError,
        /// An unknown error occured while performing the request.
        UnknownError,
        /// Invalid header name.
        HeaderInvalidName,
        /// Invalid header value.
        HeaderInvalidValue,
        /// Header name is too long.
        HeaderTooLargeName,
        /// Header value is too long.
        HeaderTooLargeValue,
        /// HTTP body exceeds prescribed limits.
        HTTPBodyTooLarge,
        /// Invalid URI.
        UriInvalid,
        /// URI is too long.
        UriTooLarge,
        /// An invalid HTTP method was provided.
        HTTPInvalidMethod,
        /// An invalid HTTP status code was provided.
        HTTPInvalidStatusCode,
        /// An invalid HTTP version was provided.
        HTTPInvalidVersion,

        /// HTTP fetch response not found.
        HTTPFetchResponseNotFound,
        /// HTTP fetch request failed.
        HTTPFetchRequestFailed,
        /// HTTP Channel is closed.
        HTTPChannelClosed
    };

    /**
     * @brief Returns a string representation of HttpError
     * 
     * @param e Error value
     * @return String representation of the error value
     */
    inline std::string to_string(HttpError e) {
        switch (e) {
            case HttpError::Success:
                return "HTTP: success";
            case HttpError::UnknownError:
                return "HTTP: unknown error";
            case HttpError::SystemError:
                return "HTTP: error in SDK function";
            case HttpError::HeaderInvalidName:
                return "HTTP: invalid header name";
            case HttpError::HeaderInvalidValue:
                return "HTTP: invalid header value";
            case HttpError::HeaderTooLargeName:
                return "HTTP: header name length exceeds limit";
            case HttpError::HeaderTooLargeValue:
                return "HTTP: header value length exceeds limit";
            case HttpError::HTTPBodyTooLarge:
                return "HTTP: http body too large error";
            case HttpError::UriInvalid:
                return "HTTP: URI value invalid";
            case HttpError::UriTooLarge:
                return "HTTP: URI value exceeds limit";
            case HttpError::HTTPInvalidMethod:
                return "HTTP: invalid fetch HTTP method";
            case HttpError::HTTPInvalidStatusCode:
                return "HTTP: invalid response status code";
            case HttpError::HTTPInvalidVersion:
                return "HTTP: invalid HTTP version";

            case HttpError::HTTPFetchResponseNotFound:
                return "Fetch: HTTP fetch response not found";
            case HttpError::HTTPFetchRequestFailed:
                return "Fetch: HTTP fetch request failed";
            case HttpError::HTTPChannelClosed:
                return "HTTP: Channel closed";
        }
    }

    /**
     * @brief Enum describing return values of functions that
     * correspond to kv modules.
     */
    enum class KVError {
        /// KV operation was successful
        Success = 0,
        /// An unknown error has ocurred while trying to perform a KV store operation.
        Unknown,
        /// The value associated with the key could not be found.
        NotFound,
        /// This application is not authorized to access this key.
        UnAuthorized
    };

    /**
     * @brief Returns a string representation of KVError
     * 
     * @param e Error value
     * @return String representation of the error value
     */
    inline std::string to_string(KVError e) {
        switch (e) {
            case KVError::Success:
                return "KV: success";
            case KVError::Unknown:
                return "KV: unknown";
            case KVError::NotFound:
                return "KV: key not found";
            case KVError::UnAuthorized:
                return "KV: unauthorized";
        }
    }

    /**
     * @brief Enum describing return values of functions that
     * correspond to storage modules.
     */
    enum class StorageError {
        /// Storage operation was successful.
        Success = 0,
        /// An error occured in the SDK library.
        SystemError,
        /// Content is required.
        EmptyContent,
        /// File name is required.
        MissingFileName,
        /// The bucket id is deleted.
        DeletedBucketID,
        /// Bucket ID is required.
        MissingBucketID,
        /// An internal error occured while performing the request.
        InternalError,
        /// The content or bucket wasn't found on the store.
        ContentNotFound,
        /// The credentials or policies entered are incorrect. Request could not be performed.
        UnAuthorized,
        /// Attributes are required.
        MissingAttributes,
        /// The required content does not exist or has been deleted.
        ContentDeleted,
        /// The attributes are invalid.
        InvalidAttributes,
        /// Resource limit exceeded.
        ResourceLimit,

        /// Storage response not found.
        StorageResponseNotFound,
        /// Storage channel closed.
        StorageChannelClosed
    };

    /**
     * @brief Returns a string representation of StorageError
     * 
     * @param e Error value
     * @return String representation of the error value
     */
    inline std::string to_string(StorageError e) {
        switch (e) {
            case StorageError::Success:
                return "Storage: success";
            case StorageError::SystemError:
                return "Storage: error occured in SDK library";
            case StorageError::EmptyContent:
                return "Storage: empty content";
            case StorageError::MissingFileName:
                return "Storage: missing query param 'file_name'";
            case StorageError::DeletedBucketID:
                return "Storage: bucket_id is deleted";
            case StorageError::MissingBucketID:
                return "Storage: missing query param 'bucket_id'";
            case StorageError::InternalError:
                return "Storage: internal error";
            case StorageError::ContentNotFound:
                return "Storage: bucket/content not found";
            case StorageError::UnAuthorized:
                return "Storage: unauthorized";
            case StorageError::MissingAttributes:
                return "Storage: missing attributes";
            case StorageError::ContentDeleted:
                return "Storage: content does not exist or was deleted";
            case StorageError::InvalidAttributes:
                return "Storage: invalid attributes";
            case StorageError::ResourceLimit:
                return "Storage: Resource limit exceeded";

            case StorageError::StorageResponseNotFound:
                return "Storage: Storage response not found";
            case StorageError::StorageChannelClosed:
                return "Storage: Storage channel closed";
        }
    }

    /**
     * @brief Convert an edjx::error::StorageError into an HTTP status code
     * 
     * @param e Storage error value
     * @return HTTP status code corresponding to the storage error value
     */
    inline edjx::http::HttpStatusCode to_http_status_code(StorageError e) {
        switch (e) {
            case StorageError::Success:
                return 200;
            case StorageError::EmptyContent:
            case StorageError::MissingFileName:
            case StorageError::MissingBucketID:
            case StorageError::MissingAttributes:
            case StorageError::InvalidAttributes:
                return 400; //HTTP_STATUS_BAD_REQUEST;
            case StorageError::ContentNotFound:
            case StorageError::ContentDeleted:
            case StorageError::StorageResponseNotFound:
                return 404; //HTTP_STATUS_NOT_FOUND;
            case StorageError::UnAuthorized:
                return 403; //HTTP_STATUS_FORBIDDEN;
            case StorageError::ResourceLimit:
                return 422; //HTTP_STATUS_UNPROCESSABLE_ENTITY,
            case StorageError::DeletedBucketID:
            case StorageError::InternalError:
            case StorageError::SystemError:
            case StorageError::StorageChannelClosed:
                return 500; //HTTP_STATUS_INTERNAL_SERVER_ERROR;
        }
    }

    /**
     * @brief Enum that describes values returned by streaming functions.
     */
    enum class StreamError {
        /// Stream function completed successfully.
        Success = 0,
        /// End of stream was reached.
        EndOfStream,
        /// An unknown error occurred.
        Unknown,
        /// System error occurred.
        SystemError,
        /// Requested stream was not found.
        StreamNotFound,
        /// Stream channel has already been closed.
        StreamChannelClosed,
        /// Read operation was attempted on a write-only stream.
        ReadOnWriteStream,
        /// Write operation was attempted on a read-only stream.
        WriteOnReadStream,
        /// Stream was already closed.
        StreamClosed,
        /// Streamed chunk exceeds size limits.
        StreamChunkTooLarge
    };

    inline std::string to_string(StreamError e) {
        switch (e) {
            case StreamError::Success:
                return "Stream: success";
            case StreamError::EndOfStream:
                return "Stream: end of stream";
            case StreamError::Unknown:
                return "Stream: unknown error";
            case StreamError::SystemError:
                return "Stream: system error";
            case StreamError::StreamNotFound:
                return "Stream: stream not found";
            case StreamError::StreamChannelClosed:
                return "Stream: stream channel is closed";
            case StreamError::ReadOnWriteStream:
                return "Stream: read attempted on write stream";
            case StreamError::WriteOnReadStream:
                return "Stream: write attempted on read stream";
            case StreamError::StreamClosed:
                return "Stream: stream is closed";
            case StreamError::StreamChunkTooLarge:
                return "Stream: stream chunk is too large";
        }
    }

}}