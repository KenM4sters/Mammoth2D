


/**
 * @brief Base class for making all dervied classes non-copyable (deletes the copy constructors).
 */
class NonCopyable 
{
protected:
    NonCopyable() = default;
    ~NonCopyable() = default;

    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};