#pragma once

using namespace std;

class Matrix;

class Vector {
    int len = 0;
    friend double det(Matrix A);
    float* v = nullptr;
    friend void show(const Vector& vect);
    friend Vector operator*(const Matrix& matr, const Vector& vect);
    friend Vector operator*(const Vector& vect, const Matrix& matr);
public:
    Vector() {
        len = 0;
        v = nullptr;
    }
    Vector(int n) {
        this->len = n;
        this->v = new float[len];
        for (int i = 0; i < len; i++) {
            this->v[i] = 0;
        }
    }

    Vector(const float* vect, int n) {
        this->len = n;
        this->v = new float[len];
        for (int i = 0; i < n; i++) {
            this->v[i] = vect[i];
        }
    }

    Vector(const Vector& vec) {
        this->len = vec.len;
        this->v = new float[len];
        for (int i = 0; i < len; i++) {
            this->v[i] = vec.v[i];
        }
    }

    void operator=(const Vector& other) {
        if (other.v != nullptr && other.len == this->len) {
            for (int i = 0; i < other.len; i++) {
                this->v[i] = other.v[i];
            }
        }
        else cout << "size is 0 or not the same" << endl;
    }

    Vector operator+(const Vector& other) {
        if (other.v != nullptr && this->len == other.len) {
            cout << "tmp\n";
            Vector tmp(other.len);
            for (int i = 0; i < len; i++) {
                tmp.v[i] = this->v[i] + other.v[i];
            }
            return tmp;
        }
        else {
            cout << "error!" << endl;
            return *this;
        }
    }

    ~Vector() {
        delete[] v;
        //cout << "destructor" << endl;
    }
};

void del(float** a, int n);

class Matrix
{
    int n = 0, m = 0;
    float** mat;
    friend double det(Matrix A);
    friend void show(const Matrix& a);
    friend void del(float** a, int n);
    friend Matrix operator*(float scalar, const Matrix& other);
    friend Vector operator*(const Matrix& matr, const Vector& vect);
    friend Vector operator*(const Vector& vect, const Matrix& matr);
public:
    Matrix() {
        mat = 0;
        n = 0, m = 0;
    }
    Matrix(int n, int m) {
        this->m = m;
        this->n = n;
        this->mat = new float* [n];
        for (int i = 0; i < n; i++) {
            this->mat[i] = new float[m];
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                this->mat[i][j] = 0;
            }
        }
    }
    Matrix(float** a, int n, int m) {
        mat = new float* [n];
        for (int i = 0; i < n; i++) {
            mat[i] = new float[m];
            for (int j = 0; j < m; j++) {
                this->mat[i][j] = a[i][j];
            }
        }
        this->n = n;
        this->m = m;
    }

    Matrix(const Matrix& matr) {
        this->n = matr.n;
        this->m = matr.m;
        this->mat = new float* [n];
        for (int i = 0; i < n; i++) {
            this->mat[i] = new float[m];
        }
        for (int i = 0; i < matr.n; i++) {
            for (int j = 0; j < matr.m; j++) {
                this->mat[i][j] = matr.mat[i][j];
            }
        }
    }

    void transpose() {
        int rows = this->n, cols = this->m;
        Matrix tmp(this->mat, rows, cols); //сохраняем копию обьекта 
        del(mat, n);
        this->mat = new float* [cols];
        for (int i = 0; i < cols; i++) {
            mat[i] = new float[rows];
            for (int j = 0; j < rows; j++) {
                this->mat[i][j] = tmp.mat[j][i];
            }
        }
        this->n = cols;
        this->m = rows;
    }

    void operator=(const Matrix& other) {
        if (this->n == other.n && this->m == other.m) {
            for (int i = 0; i < this->n; i++) {
                for (int j = 0; j < this->m; j++) {
                    this->mat[i][j] = other.mat[i][j];
                }
            }
        }
        else {
            cout << "size are not the same" << endl;
        }
    }

    Matrix& operator()(int i, int j, float a) {
        this->mat[i][j] = a;
        return (*this);
    }

    Matrix operator+(const Matrix& other) {
        int rows = this->n, cols = this->m;
        if (this->n == other.n && this->m == other.m) {
            Matrix tmp(rows, cols);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    tmp.mat[i][j] = other.mat[i][j] + this->mat[i][j];
                }
            }
            return tmp;
        }
        else {
            cout << "size are not the same!" << endl;
            return *this;
        }
    }

    Matrix operator*(const Matrix& other) {
        if (this->n == other.m && this->m == other.n) {
            Matrix tmp(min(n, m), min(n, m));
            float s = 0;
            for (int i = 0; i < this->n; i++) {
                for (int j = 0; j < other.m; j++) {
                    s = 0;
                    for (int k = 0; k < max(n, m); k++) {
                        s += this->mat[i][k] * other.mat[k][j];
                    }
                    tmp.mat[i][j] = s;
                }
            }
            return tmp;
        }
        else {
            cout << "size are not the same" << endl;
            return *this;
        }

    }

    ~Matrix() {
        del(mat, this->n);
        //cout<<"matrix was deleted" << endl;
    }
};


Matrix operator*(float scalar, const Matrix& other) {
    Matrix tmp(other.n, other.m);
    for (int i = 0; i < other.n; i++) {
        for (int j = 0; j < other.m; j++) {
            tmp.mat[i][j] = other.mat[i][j] * scalar;
        }
    }
    return tmp;
}

void del(float** a, int n) {
    for (int i = 0; i < n; i++) {
        delete[] a[i];
    }
    delete[] a;
}

Vector operator*(const Matrix& matr, const Vector& vect) {
    if (matr.m == vect.len) {
        Vector temp(matr.n);
        float s = 0;
        for (int i = 0; i < matr.n; i++) {
            s = 0;
            for (int j = 0; j < matr.m; j++) {
                s += matr.mat[i][j] * vect.v[j];
            }
            temp.v[i] = s;
        }
        return temp;
    }
    else {
        cout << "size are not the same";
        return vect;
    }
}

Vector operator*(const Vector& vect, const Matrix& matr) {
    if (matr.n == vect.len) {
        Vector temp(matr.m);
        float s = 0;
        for (int i = 0; i < matr.m; i++) {
            s = 0;
            for (int j = 0; j < matr.n; j++) {
                s += matr.mat[j][i] * vect.v[j];
            }
            temp.v[i] = s;
        }
        return temp;
    }
    else {
        cout << "size are not the same";
        return vect;
    }
}

void show(const Matrix& a) {

    for (int i = 0; i < a.n; i++) {
        for (int j = 0; j < a.m; j++) {
            cout << a.mat[i][j] << " ";
        }
        cout << endl;
    }
}

void show(const Vector& v) {

    for (int i = 0; i < v.len; i++) {
        cout << v.v[i] << " ";
    }
    cout << endl;
}

double Gauss(double **a, double* b, int n, int m) {
    float r;
    int i, j, k;
    for (j = 0; j < n - 1; j++) {
        for (i = j + 1; i < n; i++) {
            r = -a[i][j] / a[j][j];
            for (k = j; k < n; k++) {
                a[i][k] = a[i][k] + r * a[j][k];
            }
            b[i] = b[i] + r * b[j];
        }

    }
    return a;
}

double det(Matrix A){
    double **tmp_a, res = 1;
    if (A.m == A.n) {
        Vector b(A.n);
        tmp_a = Gauss(A.mat, b.v, A.n, A.m);
        for (int i = 0; i < A.n; i++) {
            res = res*tmp_a[i][i];
        }
        return res;
    }
    else {
        cout << "matrix is not square!" << endl;
        return -11111111;
    }
}
