#include <Arduino.h>
#include <functional> // Add this include

class MemoryStream : public Stream
{
private:
    uint8_t *buffer;
    size_t capacity;
    size_t position;
    size_t contentLength;
    // void (*progressCallback)(float, size_t, size_t);
    std::function<void(float, size_t, size_t)> callback; // Use std::function

public:
    MemoryStream(uint8_t *buffer, size_t capacity, size_t contentLength, std::function<void(float, size_t, size_t)> callback)
        : buffer(buffer), capacity(capacity), position(0), contentLength(contentLength), callback(callback) {}

    size_t write(uint8_t byte) override
    {
        if (position >= capacity)
            return 0;
        buffer[position++] = byte;
        reportProgress();
        return 1;
    }

    size_t write(const uint8_t *data, size_t size) override
    {
        size_t bytesToWrite = min(size, capacity - position);
        memcpy(buffer + position, data, bytesToWrite);
        position += bytesToWrite;
        reportProgress();
        return bytesToWrite;
    }

    void reportProgress()
    {
        if (callback && contentLength > 0)
        {
            float progress = (float)position / contentLength * 100.0;
            callback(progress, position, contentLength);
        }
    }

    int available() override { return capacity - position; }
    int read() override { return -1; }
    int peek() override { return -1; }
    void flush() override {}
    size_t getPosition() const { return position; }
};