#include <climits>
#include <codecvt>
#include <cstring>
#include <cuchar>
#include <iomanip>
#include <string>
#include <string_view>
// #include <iostream>

typedef int mfchar_t; // 无符号的4字节，用于容纳UCS-4的一个字符
typedef std::u32string mfstring; // 自定义的UCS-4字符串

// 把utf-8编码的字符串转换成UCS-4编码的字符串
unsigned int UTF8ToUCS4(const std::string &src, mfchar_t *dest)
{
    mfchar_t     w        = 0;
    mfchar_t     err      = '?'; // 表转码错误
    int          bytes    = 0;   // 表剩余要处理的字节数
    unsigned int curIndex = 0;

    for (size_t i = 0; i < src.length(); i++) {
        unsigned char c = (unsigned char)src[i];

        if (c <= 0x7f) // <= 0x0111 1111(即127)的说明是ascii码
        {
            // 若bytes不为0，说明出错，因为ascii码的utf-8编码只占一个字节
            if (bytes) {
                dest[curIndex++] = err;
                bytes            = 0;
            }

            // 将字符压入队列
            dest[curIndex++] = c;
        } else if (c <= 0xbf) // <= 0x1011
                              // 1111，说明是多字节的utf-8编码的第2,3,4,5,6字节
        {
            // 既然是2,3,4,5,6字节，bytes必不为0，否则出错
            if (bytes) {
                // 取出c的后六位，将w左移6位，做或预算，赋值给w，这样w就融合了c的后6位
                w = ((w << 6) | (c & 0x3f));

                // 字节数减1，因为本字节已经融合完毕
                bytes--;

                // 若后面没有字节数了，说明字节数融合完毕，成为一个完整的ucs-4的字符了，压入队列
                if (bytes == 0) {
                    dest[curIndex++] = w;
                }
            } else {
                dest[curIndex++] = err; // 出错
            }
        } else if (c <=
                   0xdf) // <= 0x1101 1111，说明是2字节的utf-8编码的第一个字节
        {
            bytes = 1; // 标记后面还有1个字节，下面类似
            w     = c &
                0x1f; // 取出后5位，注意是赋值操作，所以w的高位都将赋值为0。然后将
                      // w 与后面字节的后六位融合即可，下面类似
        } else if (c <=
                   0xef) // <= 0x1110 1111，说明是3字节的utf-8编码的第一个字节
        {
            bytes = 2;
            w     = c & 0x0f; // 取出后4位
        } else if (c <=
                   0xf7) // <= 0x1111 0111，说明是4字节的utf-8编码的第一个字节
        {
            bytes = 3;
            w     = c & 0x07; // 取出后3位
        } else if (c <=
                   0xfb) // <= 0x1111 1011，说明是5字节的utf-8编码的第一个字节
        {
            bytes = 4;
            w     = c & 0x03; // 取出后2位
        } else if (c <=
                   0xfd) // <= 0x1111 1101，说明是6字节的utf-8编码的第一个字节
        {
            bytes = 5;
            w     = c & 0x01; // 取出后1位
        } else // > 0x1111 1101的是出错，因utf-8最多6个字节
        {
            dest[curIndex++] = err;
            bytes            = 0;
        }
    }

    if (bytes) {
        dest[curIndex++] = err;
    }
    return curIndex;
}

std::string UCS4ToUTF8(const std::u32string &s)
{
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
    return conv.to_bytes(s);
}

// TODO: Support for other chatsets

// for alolang

extern "C" void string2char(int *data, long long length, char *dst)
{
    std::u32string src;
    for (long long i = 0; i < length; i++) {
        src.push_back(data[i]);
    }
    std::string result = UCS4ToUTF8(src);
    std::strncpy(dst, result.c_str(), result.length() + 1);
}

extern "C" long long __alolang_inner_load_string(char *str, long long addr)
{
    long long length = UTF8ToUCS4(std::string(str), (int *)addr);
    return length;
}
