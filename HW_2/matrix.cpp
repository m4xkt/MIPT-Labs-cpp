#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;


template<typename T>
class Matrix {
	std::vector<T> data;
	unsigned cols_, rows_;

public:
	// 1) Конструирование
    
	// создание матрицы, заполненных value
	Matrix(unsigned rows, unsigned cols, int value = 0) : rows_(rows), cols_(cols), data(rows * cols, value) {};

	// создание единичной матрицы
	static Matrix Identity(unsigned dim){
        Matrix mat(dim, dim, 0);

        for(unsigned i = 0; i < dim; i++)
            mat(i, i) = 1;
    
        return mat;
    };

	// создание случайной матрицы с заданным детерминантом
	static Matrix getSpecificDeterminant(unsigned n, T det) {

        std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
        std::uniform_real_distribution<T> dis(0.5, 2.0);
        
        Matrix result = Identity(n);
        for(unsigned i = 0; i < n; i++)
            result(i, i) = dis(gen);
        
        T current_det = 1.0;
        for(unsigned i = 0; i < n; i++)
            current_det *= result(i, i);
        
        T scale = std::pow(det / current_det, 1.0 / n);
        for(unsigned i = 0; i < n; i++)
            result(i, i) *= scale;
        
        for(unsigned i = 0; i < n; i++) {
            for(unsigned j = i + 1; j < n; j++) {
                T val = dis(gen) * 0.1;
                result(i, j) = val;
                result(j, i) = val;
            }
        }
        
        return result;
    };
    
	// ... может быть какие-то ещё инициализации для удобства ... //

	// 2) Селекторы
	unsigned rows() const { return rows_; };
    unsigned cols() const { return cols_; };

	// ... любые "getters", которые вам удобны ... //

	// 3) Методы для разминки и проверки работы вычисления детерминанта
	// транспонирую себя
	Matrix& transpose(){
        Matrix temp(cols_, rows_);
        for(unsigned i = 0; i < rows_; i++) {
            for(unsigned j = 0; j < cols_; j++)
                temp(j, i) = (*this)(i, j);
        }
        *this = temp;
        return *this;
    };

    // копирую себя, транспонируют и возвращаю
	Matrix transpose() const {
        Matrix temp(cols_, rows_);
        for(unsigned i = 0; i < rows_; i++) {
            for(unsigned j = 0; j < cols_; j++)
                temp(j, i) = (*this)(i, j);
        }
        return temp;
    };

	// 4) Доступ к элементам
	T& operator()(unsigned row, unsigned col) {
        return data[row * cols_ + col];
    };
	T operator()(unsigned row, unsigned col) const {
        return data[row * cols_ + col];
    };
	// можете организовать его через operator [], но тогда вам нужен будет 
	// прокси-класс по типу Row, который обсуждали на паре

	// 5) Любые методы, которые вам будут удобны для работы с матрицей 
	// например, созданием подматрицы, перестановка строк (столбцов), умонжение строки (столбца) на число и так далее
    void swaprows_(unsigned i, unsigned j) {
        for(unsigned k = 0; k < cols_; k++)
            std::swap((*this)(i, k), (*this)(j, k));
    }

    void scale_row(unsigned i, T factor) {
        for(unsigned k = 0; k < cols_; k++)
            (*this)(i, k) *= factor;
    }

    void add_scaled_row(unsigned i, unsigned j, T factor) {
        for(unsigned k = 0; k < cols_; k++)
            (*this)(i, k) += (*this)(j, k) * factor;
    }

};

// задача: посчитать детерминант матрицы
//ДИСКРИМИНАНТ МАТРИЦЫ :о
template<typename T>
T det(const Matrix<T>& mat) {
    unsigned n = mat.rows();
    Matrix<T> m = mat;
    T det = 1;
    int sign = 1;
    
    for(unsigned i = 0; i < n; i++) {
        unsigned pivot = i;
        for(unsigned j = i + 1; j < n; j++) {
            if(std::abs(m(j, i)) > std::abs(m(pivot, i)))
                pivot = j;
        }
        
        if(std::abs(m(pivot, i)) < 1e-12)
            return 0;
        
        if(pivot != i) {
            m.swaprows_(i, pivot);
            sign = -sign;
        }
        
        det *= m(i, i);
        
        for(unsigned j = i + 1; j < n; j++) {
            T factor = m(j, i) / m(i, i);
            for(unsigned k = i + 1; k < n; k++)
                m(j, k) -= factor * m(i, k);
        }
    }
    
    return det * sign;
}

int main() {
    Matrix<double> m1(10, 10);

    for (int i = 1, dim = 5; dim <= 200; dim*=((i==1) ? 10:2), i*=10){
        cout << "Матрица " << dim << "x" << dim << endl;
        Matrix<double> matr = Matrix<double>::getSpecificDeterminant(dim, 100.0*static_cast<double>(i));
        double opred = det(matr);
        cout << "Определитель: " << opred << endl;
        Matrix<double> matr_T = matr.transpose();
        double opred_T = det(matr_T);
        cout << "Определитель транспонированной: " << opred_T << endl;
        cout << "Гадание на оценку ((разница определителей + 1)*8): " << opred-opred_T << endl << endl;
    }

    return 0;
}