#!/usr/bin/expect

spawn scp -r -P 2222 ./libcaculate.dylib root@localhost:/Applications/
expect "*root@iPhone:"
send "alpine\n"
expect "*#"

spawn scp -r -P 2222 ./exec_file root@localhost:/Applications/
expect "*root@iPhone:"
send "alpine\n"
expect "*#"
