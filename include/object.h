/**
 * @brief Represents an big object with various properties, used for test. 
 */
#pragma once
#include <string>

struct alignas(16) Object {
    std::array<float, 4> position;
    std::array<float, 4> rotation;
    std::array<float, 4> scale;
    std::array<float, 4> color;
    std::string name;
    std::string parent;
    std::string mesh;
    std::string texture;
    std::string material;
    std::string shader;
    std::string animation;
    std::string script;
    std::string tag;
    std::string layer;
    std::string type;
    std::string subtype;
    std::string description;
    std::string author;
    std::string version;
    std::string date;
    std::string time;
    std::string path;
    std::string file;
    std::string extension;
    std::string directory;
    std::string filename;
    std::string fullpath;
    std::string relativepath;
    std::string absolutepath;
    std::string url;
    std::string guid;
    std::string id;
    std::string uuid;
    std::string hash;
    std::string crc;
    std::string md5;
    std::string sha1;
    std::string sha256;
    std::string sha512;
    std::string sha3_256;
    std::string sha3_512;
    std::string blake2b;
    std::string blake2s;
    std::string blake3;
    std::string xxhash;
    std::string murmur3;
    std::string spooky;
    std::string fnv;
    std::string city;
    std::string metro;
    std::string t1ha;
    std::string sip;
    std::string crc32;
    std::string adler32;
    std::string crc32c;
    std::string crc64;
    std::string crc64ecma;
    std::string crc64iso;
    std::string crc64jones;
    std::string crc64we;
    std::string crc64xz;
    std::string crc64z;
    std::string crc8;
    std::string crc8ccitt;
};