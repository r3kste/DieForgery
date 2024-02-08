/**
 * @namespace DiceForge
 * @brief Namespace for the DiceForge library.
 */
/**
 * @file LinearFeedbackShiftRegister.cpp
 * @brief Implementation file for the Linear Feedback Shift Register (LFSR) class.
 */

namespace DiceForge {
/**
 * @class LFSR
 * @brief A class representing a Linear Feedback Shift Register (LFSR).
 *
 * @tparam T The type of the LFSR seed and current value.
 */
template <typename T>
class LFSR {
private:
    T seed; /**< The seed value of the LFSR. */
    T curr; /**< The current value of the LFSR. */
public:
    /**
     * @brief Constructs an LFSR object with the specified seed.
     *
     * @param seed The seed value for the LFSR. Default is 1.
     */
    LFSR(T seed = 1);

    /**
     * @brief Generates a random value using the LFSR algorithm.
     *
     * @return The generated random value.
     */
    T random();

    /**
     * @brief Generates a random value between 0 and 1 using the LFSR algorithm.
     *
     * @return The generated random value between 0 and 1.
     */
    long double rand();

    /**
     * @brief Generates a random value within the specified range using the LFSR algorithm.
     *
     * @param min The minimum value of the range.
     * @param max The maximum value of the range.
     * @return The generated random value within the specified range.
     */
    T random(T min, T max);

    /**
     * @brief Destroys the LFSR object.
     */
    ~LFSR();
};

template <typename T>
LFSR<T>::LFSR(T seed) {
    if (seed <= 0) {
        seed = std::chrono::system_clock::now().time_since_epoch().count();
    }

    this->seed = seed;
    this->curr = seed;
}

template <typename T>
T LFSR<T>::random() {
    T rand_num = curr;
    bool new_bit;

    for (int i = 0; i < 4; i++) {
        rand_num ^= rand_num >> 7;
        rand_num ^= rand_num << 9;
        rand_num ^= rand_num >> 13;
        new_bit = rand_num & 1;
        // rand_num = (rand_num + (long double)new_bit) / 2;
        rand_num = (rand_num << 1) + new_bit;
        curr = (curr >> 1) | (curr << (sizeof(T) * 8 - 1));
    }

    return curr = rand_num;
}

template <typename T>
long double LFSR<T>::rand() {
    T rand_num = curr;
    bool new_bit;

    for (int i = 0; i < 4; i++) {
        rand_num ^= rand_num >> 7;
        rand_num ^= rand_num << 9;
        rand_num ^= rand_num >> 13;
        new_bit = rand_num & 1;
        // rand_num = (rand_num + (long double)new_bit) / 2;
        rand_num = (rand_num << 1) + new_bit;
        curr = (curr >> 1) | (curr << (sizeof(T) * 8 - 1));
    }

    curr = rand_num;
    return (long double)rand_num / (long double)std::numeric_limits<T>::max();
}
template <typename T>
T LFSR<T>::random(T min, T max) {
    long double rand_num = rand();
    return T(min + (max - min) * rand_num);
}

template <typename T>
LFSR<T>::~LFSR() {
    // Nothing to do here
}

} // namespace DiceForge
