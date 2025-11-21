def write():
    fd = open("/proc/my_driver", "w")
    fd.write("Hello from user2 space!\n")
    fd.close()
    pass

def read():
    fd = open("/proc/my_driver", "r")
    content = fd.read()
    print(content)
    fd.close()
    pass

def main():
    write()
    read()
    pass

if __name__ == "__main__":
    main()