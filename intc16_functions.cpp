#include "intc16.hpp"

int intc16_t::countOfIntc16 = 0;

void intc16_t::showMemAddress(){
    void* address = static_cast<void*>(&val16);

    std::cout << "(16) Memory address: " << address << "\n";
}

uint16_t intc16_t::getValue() const {
    return val16;
}

bool intc16_t::isZero() const {
    if (val16 == 0){
        return true;
    }

    return false;
}

int intc16_t::toInt(){
    return static_cast<int>(val16);
}

bool intc16_t::checkIfMax() const {
    if (val16 >= MAXIMUM_SIZE16){
        return true;
    }

    return false;
}

int intc16_t::bitCount() const{
    int count = 0;
    auto n = val16;

    while (n > 0){
        count++;
        n >>= 1;
    }

    return count;
}

bool intc16_t::isbitset(int pos) const{
    if ((val16 & (1 << pos)) != 0){
        return true;
    }

    return false;
}


void intc16_t::setbit(int pos){
    val16 |= (1 << pos);
}

void intc16_t::clearbit(int pos){
    val16 &= ~(1 << pos);
}

void intc16_t::togglebit(int pos){
    val16 ^= (1 << pos);
}

int intc16_t::countsetbits() const {
    int count = 0;
    int n = val16;

    while (n){
        count += n & 1;
        n >>= 1;
    }

    return count;
}

int intc16_t::highestbit() const{
    int pos = -1;
    int n = val16;

    while (n){
        n >>= 1;
        pos++;
    }

    return pos;
}

int intc16_t::lowestbit() const{
    for (int i = 0; i < 16; i++){
        if (val16 & (1 << i)){
            return i;
        }
    }

    return -1;
}


std::string intc16_t::toBin(){
    std::string binString = "";

    for (int i = 15; i >= 0; --i){
        // iterate from (bit 15) to bit 0
        // right shift and check the least significant bit
        if ((val16 >> i) & 1){
            binString += '1';
        }
        else {
            binString += '0';
        }
    }

    return binString;
}

std::string intc16_t::toHex(){
    std::stringstream ss;

    ss << std::hex << std::setw(4) << std::setfill('0') << val16;

    return ss.str();
}

void intc16_t::appToFile(const std::string& filename) const {
    std::ofstream file(filename, std::ios::app);

    if (!file){
        throw std::runtime_error("Failed to open file.");
    }

    file << val16 << "\n"; // each val16 stored in a new line
}

uint16_t intc16_t::getValueFromFile(const std::string& filename,
size_t position) const {
    std::ifstream file(filename);

    if (!file){
        throw std::runtime_error("Failed to open file.");
    }

    uint16_t value;
    size_t lNum = 0;

    while (file >> value){
        // check if the line number is equal to position
        if (lNum == position){
            return value;
        }

        lNum++;
    }

    throw std::out_of_range("Position exceeds records in file.");
}

void intc16_t::overwriteFile(const std::string& filename) const {
    std::ofstream file(filename, std::ios::trunc);

    if (!file){
        throw std::runtime_error("Failed to open file.");
    }

    file << val16 << "\n";
}

size_t intc16_t::countRecords(const std::string& filename) const {
    std::ifstream file(filename);

    if (!file){
        throw std::runtime_error("Failed to open file.");
    }

    size_t count = 0;
    uint16_t temp;

    while (file >> temp){
        ++count;
    }

    return count;
}

intc16_t intc16_t::rotateLeft(int n) const {
    return intc16_t((val16 << n) | (val16 >> (16 - n)));
}

intc16_t intc16_t::rotateRight(int n) const {
    return intc16_t((val16 >> n) | (val16 << (16 - n)));
}

intc16_t intc16_t::reverseBits() const {
    uint16_t x = val16;

    x = (x & 0x5555) << 1 | (x >> 1) & 0x5555;
    x = (x & 0x3333) << 2 | (x >> 2) & 0x3333;
    x = (x & 0x0F0F) << 4 | (x >> 4) & 0x0F0F;
    x = (x << 8) | (x >> 8);

    return intc16_t(x);
}

bool intc16_t::evenParity() const {
    return countsetbits() % 2 == 0;
}

void intc16_t::swap(intc16_t& other) {
    std::swap(val16, other.val16);
}

bool intc16_t::isMin() const {
    if (val16 == 0){
        return true;
    }

    return false;
}

int intc16_t::leadingZero() const {
    if (val16 == 0){
        return 16;
    }

    int count = 0;
    uint16_t n = val16;

    while ((n & 8000) == 0){
        n <<= 1;
        count++;
    }

    return count;
}

int intc16_t::trailingZero() const {
    if (val16 == 0){
        return 16;
    }

    int count = 0;
    uint16_t n = val16;

    while ((n & 1) == 0){
        n >>= 1;
        count++;
    }

    return count;
}

void intc16_t::appToBinFile(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary | std::ios::app);

    if (!file){
        throw std::runtime_error("Failed to open file.");
    }

    file.write(reinterpret_cast<const char*>(&val16), sizeof(val16));
}

uint16_t intc16_t::getValueFromBinFile(const std::string& filename, size_t pos) const {
    std::ifstream file(filename, std::ios::binary);

    if (!file){
        throw std::runtime_error("Failed to open file.");
    }

    file.seekg(pos * sizeof(val16));

    uint16_t value;

    file.read(reinterpret_cast<char*>(&value), sizeof(value));

    return value;
}

void intc16_t::appToHexFile(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file){
        throw std::runtime_error("Failed to open file.");
    }

    file << std::hex << std::uppercase << std::setw(4) << std::setfill('0')
    << val16 << "\n";
}

uint16_t intc16_t::getValueFromHexFile(const std::string& filename, size_t pos) const {
    std::ifstream file(filename);

    if (!file){
        throw std::runtime_error("Failed to open file.");
    }

    std::string line;
    size_t idx = 0;

    while (std::getline(file, line)){
        if (idx == pos){
            uint16_t value;

            std::stringstream ss(line);

            ss >> std::hex >> value;

            if (!ss){
                throw std::runtime_error("Failed to parse hex.");
            }

            return value;
        }

        idx++;
    }

    throw std::out_of_range("Position exceeds number of records.");
}

void intc16_t::delptr(intc16_t* other) const {
    if (other){
        delete other;
        other = nullptr;
    }
}

void intc16_t::a_delptr(intc16_t* other[], size_t count) const {
    if (!other) {
        return;
    }

    for (size_t i = 0; i < count; ++i){
        delete other[i];
        other[i] = nullptr;
    }

    delete[] other;
    other = nullptr;
}

intc16_t intc16_t::pow(intc16_t base, unsigned int exp) {
    uint32_t result = 1;
    uint32_t b = base.val16;

    while (exp > 0){
        if (exp & 1){
            result *= b;
        }

        b *= b;
        exp >>= 1;

        if (result > 65535){
            result = 65535;
        }
    }

    return intc16_t(result);
}

bool intc16_t::equals(const intc16_t& other) const {
    if (other.val16 == val16){
        return true;
    }

    return false;
}

bool intc16_t::m_equals(const intc16_t& other, const intc16_t& other2, char op) const {
    uint32_t a = other.val16;
    uint32_t b = other2.val16;

    switch (op) {
        case '+':
            if (a + b > 65535){
                throw std::invalid_argument("The 2 values exceed 65535.");
            }

            return (a + b) == val16;

        case '-':
            if (a < b){
                throw std::invalid_argument("The 2 values go into the negatives.");
            }

            return (a - b) == val16;

        case '*':
            if (a * b > 65535){
                throw std::invalid_argument("The 2 values exceed 65535.");
            }

            return (a * b) == val16;

        case '/':
            if (b == 0){
                throw std::invalid_argument("Division by 0 not allowed.");
            }

            return (a / b) == val16;

        default:
            throw std::invalid_argument("Please pick a valid operation. (+, -, *, /).");
    }
}

bool intc16_t::isOdd() const {
    return (val16 % 2 != 0);
}

bool intc16_t::isEven() const {
    return (val16 % 2 == 0);
}

bool intc16_t::isPalindromeH() const {
    std::stringstream ss;

    ss << std::hex << std::uppercase << val16;

    std::string hStr = ss.str();
    std::string rev = std::string(hStr.rbegin(), hStr.rend());

    return (hStr == rev);
}

bool intc16_t::isPalindromeB() const {
    std::string bStr;

    for (int i = 15; i >= 0; --i){
        bStr.push_back((val16 & (1 << i)) ? '1' : '0');
    }

    // remove leading zeros
    size_t f1 = bStr.find('1');

    if (f1 != std::string::npos){
        bStr = bStr.substr(f1);
    }

    std::string rev = std::string(bStr.rbegin(), bStr.rend());

    return (bStr == rev);
}

bool intc16_t::hasBitPattern(uint16_t pattern) const {
    return ((val16 & pattern) == pattern);
}

int intc16_t::countUnsetBits() const {
    int count = 0;

    for (int i = 0; i < 16; ++i){
        if ((val16 & (1 << i)) == 0){
            ++count;
        }
    }

    return count;
}

bool intc16_t::isPowerOfTwo() const {
    return (val16 != 0) && ((val16 & (val16 - 1)) == 0);
}

bool intc16_t::isPrime() const {
    if (val16 < 2){
        return false;
    }

    for (uint16_t i = 2; i * i <= val16; ++i){
        if (val16 % i == 0){
            return false;
        }
    }

    return true;
}

intc16_t intc16_t::n_powerOfTwo() const {
    if (val16 == 0){
        return intc16_t(1);
    }

    uint16_t n = val16;
    --n;

    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    ++n;

    return intc16_t((n > 65535) ? 65535 : n);
}

uint16_t intc16_t::m_highestBit() const {
    if (val16 == 0){
        return 0;
    }

    uint16_t m = 1;
    uint16_t n = val16;

    while (n >>= 1){
        m = (m << 1) | 2;
    }

    return m;
}

void intc16_t::swapBits(int pos1, int pos2){
    if (pos1 < 0 || pos1 > 15 || pos2 < 0 || pos2 > 15){
        throw std::invalid_argument("Position cannot be lower than 0 or higher"
        " than 15.");
    }

    bool b1 = (val16 >> pos1) & 1;
    bool b2 = (val16 >> pos2) & 1;

    if (b1 != b2){
        val16 ^= (1 << pos1) | (1 << pos2);
    }
}

int intc16_t::getCount() {
    return intc16_t::countOfIntc16;
}
