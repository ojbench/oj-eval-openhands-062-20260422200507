#ifndef BPT_MEMORYRIVER_HPP
#define BPT_MEMORYRIVER_HPP

#include <fstream>
#include <string>

using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;

template<class T, int info_len = 2>
class MemoryRiver {
private:
    fstream file;
    string file_name;
    int sizeofT = sizeof(T);

    void ensure_file_open(std::ios::openmode mode) {
        file.close();
        file.clear();
        file.open(file_name, mode | std::ios::binary);
        if (!file && (mode & std::ios::in)) {
            // try create file if not exists
            file.clear();
            fstream tmp(file_name, std::ios::out | std::ios::binary);
            tmp.close();
            file.open(file_name, mode | std::ios::binary);
        }
    }
public:
    MemoryRiver() = default;

    MemoryRiver(const string& file_name) : file_name(file_name) {}

    void initialise(string FN = "") {
        if (FN != "") file_name = FN;
        file.open(file_name, std::ios::out | std::ios::binary | std::ios::trunc);
        int tmp = 0;
        for (int i = 0; i < info_len; ++i)
            file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();
    }

    // 读出第n个int的值赋给tmp，1_base
    void get_info(int &tmp, int n) {
        if (n > info_len || n <= 0) return;
        ensure_file_open(std::ios::in);
        file.seekg(static_cast<std::streamoff>((n - 1) * sizeof(int)), std::ios::beg);
        file.read(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();
    }

    // 将tmp写入第n个int的位置，1_base
    void write_info(int tmp, int n) {
        if (n > info_len || n <= 0) return;
        ensure_file_open(std::ios::in | std::ios::out);
        file.seekp(static_cast<std::streamoff>((n - 1) * sizeof(int)), std::ios::beg);
        file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.flush();
        file.close();
    }

    // 在文件合适位置写入类对象t，并返回写入的位置索引index
    int write(T &t) {
        ensure_file_open(std::ios::in | std::ios::out);
        file.seekp(0, std::ios::end);
        std::streamoff pos = file.tellp();
        file.write(reinterpret_cast<char *>(&t), sizeofT);
        file.flush();
        file.close();
        return static_cast<int>(pos);
    }

    // 用t的值更新位置索引index对应的对象
    void update(T &t, const int index) {
        ensure_file_open(std::ios::in | std::ios::out);
        file.seekp(static_cast<std::streamoff>(index), std::ios::beg);
        file.write(reinterpret_cast<char *>(&t), sizeofT);
        file.flush();
        file.close();
    }

    // 读出位置索引index对应的T对象的值并赋值给t
    void read(T &t, const int index) {
        ensure_file_open(std::ios::in);
        file.seekg(static_cast<std::streamoff>(index), std::ios::beg);
        file.read(reinterpret_cast<char *>(&t), sizeofT);
        file.close();
    }

    // 删除位置索引index对应的对象(不涉及空间回收时，可忽略此函数)
    void Delete(int index) {
        (void)index; // no-op for this simplified version
    }
};


#endif //BPT_MEMORYRIVER_HPP
