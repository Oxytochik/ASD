#include <stdexcept>

template <class T>
class DSU {
private:
    T* _parent;
    T* _rank;
    size_t _size;

    void check_index(T x) const;

public:
    explicit DSU(size_t size);
    DSU(const DSU& other);
    ~DSU();

    DSU& operator=(const DSU& other);

    void union_sets(T x, T y);
    T find(T x);
    T find_rec(T x);
    bool connected(T x, T y);

    size_t size() const;
};

template <class T>
void DSU<T>::check_index(T x) const {
    if (x < 0 || x >= _size) {
        throw std::out_of_range("DSU index out of range");
    }
}

template <class T>
DSU<T>::DSU(size_t size) : _size(size) {
    if (size == 0) {
        throw std::invalid_argument("DSU size cannot be zero");
    }

    _parent = new T[size];
    _rank = new T[size];

    for (size_t i = 0; i < size; ++i) {
        _parent[i] = i;
        _rank[i] = 0;
    }
}

template <class T>
DSU<T>::DSU(const DSU& other) : _size(other._size) {
    _parent = new T[_size];
    _rank = new T[_size];

    for (size_t i = 0; i < _size; ++i) {
        _parent[i] = other._parent[i];
        _rank[i] = other._rank[i];
    }
}

template <class T>
DSU<T>::~DSU() {
    delete[] _parent;
    delete[] _rank;
}

template <class T>
DSU<T>& DSU<T>::operator=(const DSU& other) {
    if (this != &other) {
        delete[] _parent;
        delete[] _rank;

        _size = other._size;
        _parent = new T[_size];
        _rank = new T[_size];

        for (size_t i = 0; i < _size; ++i) {
            _parent[i] = other._parent[i];
            _rank[i] = other._rank[i];
        }
    }
    return *this;
}

template <class T>
void DSU<T>::union_sets(T x, T y) {
    check_index(x);
    check_index(y);

    T root_x = find(x);
    T root_y = find(y);

    if (root_x == root_y) {
        return;
    }

    if (_rank[root_x] > _rank[root_y]) {
        _parent[root_y] = root_x;
    }
    else if (_rank[root_x] < _rank[root_y]) {
        _parent[root_x] = root_y;
    }
    else {
        _parent[root_y] = root_x;
        _rank[root_x]++;
    }
}

template <class T>
T DSU<T>::find(T x) {
    check_index(x);

    T root = x;
    while (root != _parent[root]) {
        root = _parent[root];
    }

    while (x != root) {
        T next = _parent[x];
        _parent[x] = root;
        x = next;
    }

    return root;
}

template <class T>
T DSU<T>::find_rec(T x) {
    check_index(x);

    if (_parent[x] != x) {
        _parent[x] = find_rec(_parent[x]);
    }
    return _parent[x];
}

template <class T>
bool DSU<T>::connected(T x, T y) {
    return find(x) == find(y);
}

template <class T>
size_t DSU<T>::size() const {
    return _size;
}

bool** generate(int X, int Y, int N, int M) {
    if ((N < 2) || (M < 2)) { throw std::invalid_argument("Wrong size!"); }

    int size_maze = N * M;
    DSU<int> maze(size_maze);

    int new_N = N * 2 + 1, new_M = M + 1, size_walls = new_N * new_M;
    bool** mass_the_walls_of_the_maze = new bool* [new_N];
    for (int i = 0; i < new_N; i++) {
        mass_the_walls_of_the_maze[i] = new bool[new_M];
    }

    for (int i = 0; i < new_N; i++) {
        for (int j = 0; j < new_M; j++) {
            if ((i % 2 == 0) && (j == M)) mass_the_walls_of_the_maze[i][j] = false;
            else mass_the_walls_of_the_maze[i][j] = true;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int random_on_the_right = rand() % 2;
            int random_on_the_bottom = rand() % 2;
            if ((random_on_the_right == 0) && (j != (M - 1)) && (maze.find_rec(i * M + j) != maze.find_rec(i * M + j + 1))) {   // + ???????? ?? ????????? ? dsu, ????? ?? ????? ??????? ?????
                maze.union_sets(i * M + j, i * M + j + 1);
                mass_the_walls_of_the_maze[i * 2 + 1][j + 1] = false;
            }
            if ((random_on_the_bottom == 0) && (i != (N - 1)) && (maze.find_rec(i * M + j) != maze.find_rec(i * M + j + M))) {   // + ???????? ?? ????????? ? dsu, ????? ?? ????? ??????? ?????
                maze.union_sets(i * M + j, i * M + j + M);
                mass_the_walls_of_the_maze[i * 2 + 2][j] = false;
            }
        }
    }

    int i_x = X / M, j_x = X % M, i_y = Y / M, j_y = Y % M;
    if (i_x == 0) mass_the_walls_of_the_maze[0][j_x] = false;
    else if (i_x == N - 1) mass_the_walls_of_the_maze[new_N - 1][j_x] = false;
    else if (j_x == 0) mass_the_walls_of_the_maze[i_x * 2 + 1][0] = false;
    else if (j_x == M - 1) mass_the_walls_of_the_maze[i_x * 2 + 1][new_M - 1] = false;

    if (i_y == 0) mass_the_walls_of_the_maze[0][j_y] = false;
    else if (i_y == N - 1) mass_the_walls_of_the_maze[new_N - 1][j_y] = false;
    else if (j_y == 0) mass_the_walls_of_the_maze[i_y * 2 + 1][0] = false;
    else if (j_y == M - 1) mass_the_walls_of_the_maze[i_y * 2 + 1][new_M - 1] = false;

    if (maze.find_rec(X) == maze.find_rec(Y)) return mass_the_walls_of_the_maze;
    else {
        for (int i = 0; i < new_N; i++) {
            delete[] mass_the_walls_of_the_maze[i];
        }
        delete[] mass_the_walls_of_the_maze;

        return generate(X, Y, N, M);
    }
}

//void print(bool** labirint, int N, int M) {
//    int new_N = N * 2 + 1, new_M = M + 1;
//    for (int i = 0; i < new_N; i++) {
//        for (int j = 0; j < new_M; j++) {
//            if (i % 2 == 0) {
//                //std::cout « " ";
//                if (labirint[i][j] == true) std::cout « " --";
//                else std::cout « "   ";
//            }
//            else {
//                if (labirint[i][j] == true) std::cout « "|  ";
//                else std::cout « "   ";
//            }
//        }
//        std::cout « "\n";
//    }

    //for (int i = 0; i < new_N; i++) {
    //    for (int j = 0; j < new_M; j++) {
    //        if (i % 2 == 0) {
    //            //std::cout « " ";
    //            if (labirint[i][j] == true) std::cout « " 1 ";
    //            else std::cout « " 0 ";
    //        }
    //        else {
    //            if (labirint[i][j] == true) std::cout « " 1 ";
    //            else std::cout « " 0 ";
    //        }
    //    }
    //    std::cout « "\n";
    //}
//}
//ñäåëàé îáçîð