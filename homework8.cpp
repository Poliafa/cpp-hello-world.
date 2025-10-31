#include  <iostream>
#include <cmath>
#include <cassert>
using namespace std;

class Vector3D{
    double x,y,z;
    mutable double cached_magnitude;
    mutable bool cache_valid;
    static int total_vectors;
public:
    Vector3D(double x = 0.0, double y = 0.0, double z = 0.0)
    : x(x), y(y), z(z), cache_valid(false){
        total_vectors++;
    }
    Vector3D(const Vector3D& other)
    : x(other.x), y(other.y), z(other.z), cache_valid(false){
        total_vectors++;
    }
    Vector3D& operator=( const Vector3D& other){
        if (this!=&other){
            x = other.x;
            y = other.y;
            z = other.z;
            cache_valid= false;
        }
        return *this;
    }
    ~Vector3D(){
        total_vectors--;
    }
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }

    double getMagnitude() const{
        if (!cache_valid){
            cached_magnitude =sqrt(x*x+y*y+z*z);
            cache_valid = true;
            cout << "Lengt vecrot and cached:"<< cached_magnitude<< endl;
        }
        return cached_magnitude;
    }
    Vector3D normalize() const{
        double magnitude = getMagnitude();
        if (magnitude==0.0){
            return Vector3D(0,0,0);
        }
        return Vector3D(x/magnitude, y/magnitude,z/magnitude);
    }
    static double dotProduct(const Vector3D& a, const Vector3D& b){
        return a.x *b.x + a.y*b.y + a.z* b.z;
    }
    bool operator()(double component_value) const {
        return (x == component_value) || (y == component_value) || (z == component_value);
    }
    static int getTotalVectors() {
        return total_vectors;
    }
    Vector3D operator+( const Vector3D& other){
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }
    Vector3D operator-( const Vector3D& other){
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }
    Vector3D operator*(double scalar) const{
        return Vector3D(x*scalar, y *scalar, z *scalar);
    }
    bool operator==(const Vector3D& other) const {
        double epsilon = 1e-10; // Малая величина для сравнения double
        return (std::abs(x - other.x) < epsilon) &&
               (std::abs(y - other.y) < epsilon) &&
               (std::abs(z - other.z) < epsilon);
    }
    bool operator!=( const Vector3D& other) const{
        return !(*this == other);
    }
    friend ostream& operator<<(ostream& os, const Vector3D& vec);
    friend class Vector3Dtest;
};

int Vector3D::total_vectors = 0;

ostream& operator<<(ostream& os, const Vector3D& vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}


class Vector3Dtest{
    static bool validateComponent(double component){
        return !isnan(component) && !isinf(component);
    }
    public:
    static void testStaticCounter() {
        cout << "=== Test static Counter ===" << endl;
        int initial_count = Vector3D::getTotalVectors();
        {
            Vector3D v1(1, 2, 3);
            Vector3D v2(4, 5, 6);
            assert(Vector3D::getTotalVectors() == initial_count + 2);
            cout << "Total vector after 2: " << Vector3D::getTotalVectors() << endl;
        }
        assert(Vector3D::getTotalVectors() == initial_count);
        cout << "Total vector after delete:  " << Vector3D::getTotalVectors() << endl;
        cout << "Test right!" << endl << endl;
    }
    static void testVectorAddition(){
        cout << "=== Test Vector Addition ===" << endl;
        Vector3D v1(1, 2, 3);
        Vector3D v2(4, 5, 6);
        Vector3D result = v1 + v2;
        assert(result.getX() == 5);
        assert(result.getY() == 7);
        assert(result.getZ() == 9);
        cout << v1 << "+" << v2<<"="<<result<<endl;
        cout << "Test right"<< endl;
    }
    static void testVectorSubtraction(){
        cout << "=== Test Vector Subtraction ===" << endl;
        Vector3D v1(1, 2, 3);
        Vector3D v2(4, 5, 6);
        Vector3D result = v1 - v2;
        assert(result.getX() == -3);
        assert(result.getY() == -3);
        assert(result.getZ() == -3);
        cout << v1 << "-" << v2<<"="<<result<<endl;
        cout << "Test right"<< endl;
    }
    static void testscalarMultiplication(){
        cout << "=== Test scalarMultiplication ===" << endl;
        Vector3D v1(1, 2, 3);
        Vector3D result = v1 *2;
        assert(result.getX() == 2.0);
        assert(result.getY() == 4.0);
        assert(result.getZ() == 6.0);
        cout << v1 << "*2"<<"="<<result<<endl;
        cout << "Test right"<< endl;
    }
    static void testEqualityOperators(){
        cout << "=== Test EqualityOperators ===" << endl;
        Vector3D v1(1.0, 2.0, 3.0);
        Vector3D v2(1.0, 2.0, 3.0);
        Vector3D v3(2.0, 2.0, 3.0);
        
                cout << "v1 == v2: " << (v1 == v2) << endl;
        cout << "v1 != v3: " << (v1 != v3) << endl;
        cout << "Difference in x: " << abs(v1.getX() - v3.getX()) << endl;
        cout << "Epsilon: " << 1e-10 << endl;

        assert(v1 == v2);
        assert(v1 != v3);
        cout << "Test right"<< endl;
    }
    static void testDotProduct(){
        cout << "=== Test Dot Productn ===" << endl;
        Vector3D v1(1, 2, 3);
        Vector3D v2(4, 5, 6);
        double dot = Vector3D:: dotProduct(v1,v2);
        assert(dot ==32);
        cout << "Test right"<< endl;
    }
    static void testNormalization(){
        cout << "=== Test Normalization ===" << endl;
        Vector3D v(3, 4, 0);
        Vector3D normalized = v.normalize(); // Исправлено имя
        double mag = normalized.getMagnitude();
        assert(abs(mag-1.0)< 1e-10);
        assert(abs(normalized.getX() - 0.6) < 1e-10);
        assert(abs(normalized.getY() - 0.8) < 1e-10);
        assert(abs(normalized.getZ() - 0.0) < 1e-10);
        cout << "Normalized " << v << " = " << normalized << endl;
        cout << "Length normalized vector: " << mag << endl;
        cout << "Test right"<< endl;
    }
    static void testFunctionalObject() {
        cout << "=== Test Functional Object  ===" << endl;
        Vector3D v(1, 2, 3);
        
        bool has_two = v(2);
        assert(has_two == true);
        
        bool has_five = v(5);
        assert(has_five == false);
        
        cout << "Vector " << v << " in 2: " << has_two << endl;
        cout << "Vector " << v << " in 5: " << has_five << endl;
        cout << "Test right"<< endl;
    }
    static void runAllTests(){
        cout << "=== Run all tests  ===" << endl;
        testStaticCounter();
        testVectorSubtraction();
        testVectorAddition();
        testscalarMultiplication();
        testEqualityOperators();
        testDotProduct();
        testNormalization();
        testFunctionalObject();

        cout << "Tests right"<< endl;
    }
};

void demonstrateVectorOperations(){
    cout << "demonstrate Vector Operation"<< endl;
    Vector3D v1(1, 2, 3);
    Vector3D v2(4, 5, 6);
    cout << "Vector 1:" << v1<< endl;
    cout << "Vector 2:" << v2<< endl;

    Vector3D sum = v1 + v2;
    Vector3D diff = v1 - v2;
    Vector3D scaled = v1 * 2.0;
    cout << "summ:"<< sum <<endl;
    cout << "diff:"<< diff <<endl;
    cout << "scalar:"<< scaled <<endl;

    double dot = Vector3D::dotProduct(v1,v2);
    cout << "dotProduct:"<<dot<<endl;

    Vector3D normolize = v1.normalize();
    cout << "Normolize vector 1:"<< normolize <<endl;
    cout << "Lenght Normolize vector 1:"<< normolize.getMagnitude() <<endl;
    
    cout << v1 <<endl;
    cout << "2 in vector 1:"<< v1(2) <<endl;
    cout << "7 in vector 1:"<< v1(7) <<endl;
    
    cout << "Static vector:"<< Vector3D::getTotalVectors() <<endl;
}

int main() {

    cout << "Run code" << endl;
    demonstrateVectorOperations();

    Vector3Dtest::runAllTests();
    cout << "Finish code" << endl;

    return 0;

}