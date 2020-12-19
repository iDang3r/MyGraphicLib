#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <climits>

#include "dump.h"

namespace Engine {
    #include "File_manager.hpp"
};

void Engine::File_manager::rescan_dir()
{
    subdirs.clear();

    DIR* dir_fd = opendir(current_dir.c_str());

    dirent* dir_str = readdir(dir_fd);

    while (NULL != dir_str) {
        subdirs.emplace_back(dir_str->d_name, dir_str->d_type);

        dir_str = readdir(dir_fd);
    }
    
    closedir(dir_fd);

    void* ptr = realpath(current_dir.c_str(), buff);
    if (NULL == ptr) {
        perror("realpath");
        exit(1);
    }
    current_dir = std::move(std::string(buff));

    std::sort(subdirs.begin(), subdirs.end());
}

Engine::File_manager::File_manager(const std::string &current_dir) : current_dir(current_dir)
{
    rescan_dir();
}

const std::string& Engine::File_manager::get_current_dir() const
{
    return current_dir;
}

int Engine::File_manager::get_dir_size() const
{
    return static_cast<int>(subdirs.size());
}

const std::string& Engine::File_manager::get_subdir_name(int num) const
{
    if (num < 0 || get_dir_size() <= num) {
        dump(DUMP_INFO, "incorrect num of subdir");
        exit(1);
    }

    return subdirs[num].name;
}

bool Engine::File_manager::is_subdir_file(int num) const
{
    if (num < 0 || get_dir_size() <= num) {
        dump(DUMP_INFO, "incorrect num of subdir");
        exit(1);
    }

    return DT_REG == subdirs[num].type;
}

bool Engine::File_manager::is_subdir_dir(int num) const
{
    if (num < 0 || get_dir_size() <= num) {
        dump(DUMP_INFO, "incorrect num of subdir");
        exit(1);
    }

    return DT_DIR == subdirs[num].type;
}

void Engine::File_manager::go_to_subdir(int num)
{
    if (num < 0 || get_dir_size() <= num) {
        dump(DUMP_INFO, "incorrect num of subdir");
        exit(1);
    }

    if (!is_subdir_dir(num)) {
        dump(DUMP_INFO, "not directory");
        exit(1);
    }

    current_dir += "/" + subdirs[num].name;

    rescan_dir();
}

Engine::File_manager::Dir::Dir(const std::string& name, int type) : name(name), type(type) {}

bool Engine::File_manager::Dir::operator<(const Dir& dir) const
{
    return name < dir.name;
}