#pragma once 

#include <string>
#include <vector>
#include <climits>

class File_manager
{
private:
public:
    char buff[PATH_MAX] = {};

    class Dir {
    public:
        std::string name;
        int type;

        Dir(const std::string& name, int type) : name(name), type(type) {}

        bool operator<(const Dir& dir) const
        {
            return name < dir.name;
        }
    };

    std::string current_dir;
    std::vector<Dir> subdirs;

    void rescan_dir();

public:

    File_manager(const std::string &current_dir);

    const std::string& get_current_dir() const;

    int get_dir_size() const;

    const std::string& get_subdir_name(int num) const;

    bool is_subdir_file(int num) const;

    bool is_subdir_dir(int num) const;

    void go_to_subdir(int num);

};