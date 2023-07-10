import os


def all_files_in_dir(root_dir):
    file_paths = []
    for root, dirs, files in os.walk(root_dir):
        for file in files:
            file_paths.append(os.path.join(root, file))
    return file_paths


def make_clion_dir():
    clion_dir = os.path.join(os.curdir, "Clion")
    clion_dir_inc = os.path.join(clion_dir, "Inc")
    clion_dir_src = os.path.join(clion_dir, "Src")
    if not os.path.exists(clion_dir):
        os.mkdir(clion_dir)
    if not os.path.exists(clion_dir_inc):
        os.mkdir(clion_dir_inc)
    if not os.path.exists(clion_dir_src):
        os.mkdir(clion_dir_src)


def copy2clion(dir_paths):
    for dir_path in dir_paths:
        file_paths = all_files_in_dir(dir_path)
        for file_path in file_paths:
            if file_path.endswith(".c"):
                clion_file_path = os.path.join(os.curdir, "Clion", "Src")
                os.system("copy %s %s" % (file_path, clion_file_path))
            elif file_path.endswith(".h"):
                clion_file_path = os.path.join(os.curdir, "Clion", "Inc")
                os.system("copy %s %s" % (file_path, clion_file_path))


def all_dir_names(root_dir):
    dir_names = []
    for dir_name in os.listdir(root_dir):
        if os.path.isdir(dir_name) and dir_name != "Clion" and dir_name != "DebugConfig" and (
                not dir_name.startswith(".")) and not dir_name.startswith("cmake"):
            dir_names.append(dir_name)
    return dir_names


if __name__ == '__main__':
    make_clion_dir()
    all_dir_names = all_dir_names(os.curdir)
    copy2clion(all_dir_names)
