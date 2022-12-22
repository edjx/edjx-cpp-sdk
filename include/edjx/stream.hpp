#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "error.hpp"

namespace edjx {

/// Streaming API
namespace stream {

    /**
     * @brief This is a base class for the streams.
     */
    class BaseStream {
    public:
        /**
         * @brief Constructs a new empty Base Stream object.
         */
        inline BaseStream() : initialized(false) {}
        /**
         * @brief Constructs a new initilized Base Stream object
         * 
         * @param sd Stream descriptor
         */
        inline BaseStream(uint32_t sd) : sd(sd), initialized(true) {}

        /**
         * @brief Get the stream descriptor of the stream.
         * 
         * The stream descriptor may be undefined if is_open() is false.
         * 
         * @return uint32_t Stream descriptor
         */
        inline uint32_t get_sd() const {
            return sd;
        }
        /**
         * @brief Check whether the stream object has been initialized or not.
         * 
         * @return true The stream object has been initialized
         * @return false The stream object is not initialized
         */
        bool is_initialized() const {
            return initialized;
        }
        /**
         * @brief Close the stream.
         * 
         * This method cleanly ends the streaming.
         * 
         * @return Returns edjx::error::StreamError::Success on success,
         * some other value on failure.
         */
        edjx::error::StreamError close();
    protected:
        /// The stream descriptor
        uint32_t sd;
        /// True if the stream is initialized, false if it is closed
        bool initialized;
    };

    /**
     * @brief This class represents a write stream
     */
    class WriteStream : public BaseStream {
    public:
        /**
         * @brief Constructs a new empty Write Stream object
         */
        inline WriteStream() {}
        /**
         * @brief Constructs a new initilized Write Stream object
         * 
         * @param sd Stream descriptor
         */
        inline WriteStream(uint32_t sd) : BaseStream(sd) {}
        /**
         * @brief Write a chunk of text into the write stream.
         * 
         * @param text A chunk of text
         * @return Returns edjx::error::StreamError::Success on success,
         * some other value on failure.
         */
        edjx::error::StreamError write_chunk(const std::string & text);
        /**
         * @brief Write a chunk of binary data into the write stream.
         * 
         * @param bytes A chunk of binary data
         * @return Returns edjx::error::StreamError::Success on success,
         * some other value on failure.
         */
        edjx::error::StreamError write_chunk(const std::vector<uint8_t> & bytes);

        /**
         * @brief Aborts sending data and closes the stream.
         * 
         * This method abruptly ends the streaming.
         * 
         * Difference between close() and abort():
         *   - When HTTP/1.1 is used:
         *     - close() sends a terminating chunk
         * of size zero to signalize the end of the stream
         *     - abort() stops streaming without sending
         * the terminating chunk
         * 
         * Note that close() is not available after abort() is called.
         * 
         * @return Returns edjx::error::StreamError::Success on success,
         * some other value on failure.
         */
        edjx::error::StreamError abort();
    };

    /**
     * @brief Read stream class
     */
    class ReadStream : public BaseStream {
    public:
        /**
         * @brief Constructs a new empty Read Stream object
         */
        inline ReadStream() {}
        /**
         * @brief Constructs a new initilized Read Stream object
         * 
         * @param sd Stream descriptor
         */
        inline ReadStream(uint32_t sd) : BaseStream(sd) {}
        /**
         * @brief Read a chunk of binary data from the stream
         * 
         * @param result The received chunk of binary data
         * @return Returns edjx::error::StreamError::Success on success,
         * some other value on failure.
         */
        edjx::error::StreamError read_chunk(std::vector<uint8_t> & result);

        /**
         * @brief Pipes a read stream into a write stream.
         * 
         * After all data is transmitted, both streams are automatically closed.
         * 
         * @param write_stream Write stream to which data from the
         * read stream will be sent.
         * @return Returns edjx::error::StreamError::Success on success,
         * some other value on failure.
         */
        edjx::error::StreamError pipe_to(WriteStream & write_stream);

        /**
         * @brief Reads and returns all data from the stream until the end of stream.
         * 
         * This method does not close the stream.
         * 
         * @param result All data received from the read stream will be copied here
         * @return Returns edjx::error::StreamError::Success on success,
         * some other value on failure.
         */
        edjx::error::StreamError read_all(std::vector<uint8_t> & result);
    };

}}