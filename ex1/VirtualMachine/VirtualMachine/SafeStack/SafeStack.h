//
// Created by user on 02.10.18.
//

#ifndef SAFESTACKCSTYLE_SAFESTACK_H
#define SAFESTACKCSTYLE_SAFESTACK_H

#include <utility>
#include <ostream>

#ifdef DEBUG
#define DUMP \
         dump(std::cout); \

#else
#define DUMP
#endif

#define CHECK_BEFORE_AND_SET_CHECKSUM(block) \
        auto codeOfIsUnchanged = isUnchanged(); \
        if (codeOfIsUnchanged != 0) {   \
         DUMP \
         return codeOfIsUnchanged; \
        }   \
        block  \
        setCheckSum();  \

#define CHECK_BEFORE_PAIR_AND_SET_CHECKSUM(block) \
        auto codeOfIsUnchanged = isUnchanged(); \
        if (codeOfIsUnchanged != 0) {   \
         DUMP \
         return std::make_pair(POISON_, codeOfIsUnchanged); \
        }   \
        block  \
        setCheckSum();  \



/// SafeStack not look for own memory carefully
/// \tparam Type - type of elements in stack must have hash() function
template <typename Type> class SafeStack {
    /// Kanareika Before variables
    int KANAREIKA_STARTING_ = 0xBEDABEDA;

    /// max size of stack container
    static const int MAX_SIZE_ = 100;
    /// simple number to calculate checksum
    static const int SIMPLE_NUMBER_ = 11;
    /// module to calculate checksum
    static const int MODULE_ = 10000001;

    /// Stack - container
    Type container_[MAX_SIZE_];
    /// Real count of elemnts now in stack
    int count_ = 0;
    /// Poisn value that can be used in stack
    Type POISON_;

    /// CurrentChecksum
    int checkSum_ = 0xBEDABEDA;
    /// Kaanreika after variables
    int KANAREIKA_ENDING_ = 0xBEDABEDA;

public:
    enum ErrorCodes {
        OK, //!< Everything is OK // 0
        ErrorCountSize, //!< Size of Count is too big or small // 1
        ErrorPoison, //!< Posion value not in array // 2
        ErrorCheckSum, //!< Current Checksum is unequal with saved Checksum // 3
        ErrorPop, //!< Nothin to Pop // 4
        ErrorPush, //!< Container is full // 5
        ErroKanareika //!< Kanareika is not equal to 0xBEDABEDA // 6
    };



public:
    /// Fill container with poison_ value, count checksum
    /// \param poison_ - element that will not be in stack
    SafeStack(Type poison_) : POISON_(poison_) {
        std::fill(container_, container_ + MAX_SIZE_, POISON_);
        setCheckSum();
    }
    /// Check if checksum not changed
    /// \return ErrorCode
    ErrorCodes isUnchanged() const {
        auto codeOfIsValide = isValid();
        if (codeOfIsValide != 0) {
            return codeOfIsValide;
        }

        int currentCheckSum = getCheckSum();
        if (currentCheckSum != checkSum_) {
            return ErrorCheckSum; // checkSum_ != currentCheckSum
        }

        return OK; // everything is OK
    }
    /// Remove Last element
    /// If it has no last element error returned
    /// \return ErrorCode
    ErrorCodes pop() {
        if (count_ == 0) {
            DUMP
            return ErrorPop; // Nothing to POP
        }
        CHECK_BEFORE_AND_SET_CHECKSUM({count_--; container_[count_] = POISON_;});
        return OK;
    }
    /// Add element to front
    /// If stack is full returns Error
    /// \param element - element to push
    /// \return ErrorCode
    ErrorCodes push(Type element) {
        if (count_ == MAX_SIZE_) {
            DUMP
            return ErrorPush; // Container is full
        }
        CHECK_BEFORE_AND_SET_CHECKSUM(container_[count_] = element; count_++;);
        return OK;
    }
    /// CAUTION!!! - Not use it if you are not sure!!!
    /// \return front element  without checking
    Type getFrontUnsafe() const {
        if (count_ >= 1) {
            return container_[count_ - 1];
        }
        // ERROR!!!!
    }
    ///
    /// \return pair where first element - is Front element if exists, else Poison value. second - ErrorCode
    std::pair<Type, ErrorCodes> getFrontSafe()     {
        if (count_ == 0) {
            return std::make_pair(POISON_, ErrorPop); // Nothing to show
        }
        CHECK_BEFORE_PAIR_AND_SET_CHECKSUM()

        return std::make_pair(getFrontUnsafe(), OK);
    }

private:
#ifdef DEBUG
    /// Show all relevant information of object, IF DEBUG MODE
    /// \param out - stream to write
    void dump(std::ostream& out) const {

    out << "class SafeStack {" << std::endl;
    out << "    /// Kanareika Before variables" << std::endl;
    out << "    int KANAREIKA_STARTING_ = " << KANAREIKA_STARTING_ << " --- MUST BE " << 0xBEDABEDA << std::endl;
    out << "    /// Stack - container_" << std::endl;
    out << "    "<< typeid(Type).name()  << " container_[MAX_SIZE_] { " << std::endl;

    for(int i = 0; i < MAX_SIZE_; i++) {
        out << "    container_[" << i << "] = " << container_[i];
        if (i >= count_) {
            out << " * <---- MUST BE POISON_, " << "We SUPPOSE THAT POISON_ = " << POISON_;
        }
        out << std::endl;
    }


    out << "     }" << std::endl;
    out << "    /// Real count_ of elemnts now in stack" << std::endl;
    out << "    int count_ = " << count_ << std::endl;
    out << "    /// Poisn value that can be used in stack" << std::endl;
    out << "    " << typeid(Type).name() << " POISON_ = " << POISON_ << std::endl;
    out << "    /// CurrentChecksum" << std::endl;
    out << "    int checkSum_ = " << checkSum_ << std::endl;
    out << "    /// Kaanreika after variables" << std::endl;
    out << "   int KANAREIKA_ENDING_ = " << KANAREIKA_ENDING_ << " --- MUST BE " << 0xBEDABEDA << std::endl;
    out << "}" << std::endl;

}
#endif
    /// checksum calculation
    /// \return current checksum
    int getCheckSum() const {
        int cacheSum  = 5;
        std::hash<Type> hashFunc;
        for (int i = 0; i < count_; i++) {
            cacheSum = ((cacheSum * SIMPLE_NUMBER_) + hashFunc(container_[i])) % MODULE_;
        }
        return cacheSum;
    }
    /// Calculate and set new checksum
    void setCheckSum() {
        checkSum_ = getCheckSum();
    }
    /// Check if kanareika is not changed, array not changed, etc.
    /// \return ErrorCode
    ErrorCodes isValid() const {
        if (count_ < 0 || count_ >= MAX_SIZE_) {
            return ErrorCountSize; // error in size of count_
        }
        if (KANAREIKA_STARTING_ != KANAREIKA_ENDING_ || KANAREIKA_ENDING_ != 0xBEDABEDA) {
            return ErroKanareika; // Error with Kanareika
        }
        for (int i = count_; i < MAX_SIZE_; i++) {
            if (container_[i] != POISON_) {
                return ErrorPoison; // POISON_ VALUE NOT IN ARRAY
            }
        }
        return OK; // everything is OK
    }

};


#endif //SAFESTACKCSTYLE_SAFESTACK_H