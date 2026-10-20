# mybash — 一个基于 fork + exec 的简易 Shell

用 C 语言在 Linux 下实现的命令行解释器，学习目的是搞清楚 Shell 的工作原理：命令如何被解析、外部命令如何被执行、内置命令和外部命令的区别。

## 功能

- 命令解析：以空格切分命令与参数（`strtok`）
- 外部命令执行：`fork` + `execv`，支持绝对路径、相对路径、固定 bin 目录三种查找方式
- 内置命令：`cd`（`chdir` 实现）、`exit`
- 彩色提示符：`用户名@主机名 工作目录 $`，root 用户显示 `#`
- 子进程结束后由父进程 `wait` 回收

## 目录结构

```
mybsh.c          Shell 主程序
commands/        自实现的核心命令（学习用）
  ls.c           ls 的简单实现
  pwd.c          pwd 的简单实现
  clear.c        clear 的简单实现
  myps.c         ps 的简单实现（读取 /proc）
  mykill.c       kill 的简单实现
  fork.c         fork 返回值行为的验证实验
```

## 编译与运行

```bash
gcc -o mybsh mybsh.c
./mybsh
```

自实现命令单独编译：

```bash
gcc -o mybin/ls commands/ls.c
gcc -o mybin/pwd commands/pwd.c
# 其余同理
```

## 学到的关键点

1. **`fork` 一次调用、两次返回**：父进程中返回子进程 PID，子进程中返回 0，出错返回 -1
2. **`execv` 不新建进程**：它把当前进程的代码段整体替换，所以必须先 `fork` 出子进程再执行，否则 Shell 自己就被替换掉了
3. **`cd` 为什么必须内置**：`chdir` 改的是调用进程自己的工作目录。如果 `cd` 作为外部命令在子进程里执行，改的是子进程的目录，父进程（Shell）不受影响
4. **`wait` 回收子进程**：不回收会产生僵尸进程
5. **命令行解析**：`strtok` 按空格切分出 `argv` 数组，传给 `execv`

## 已知限制（学习迭代中的取舍）

- 不支持管道 `|`、重定向 `>` `<`、通配符 `*`
- 不支持后台运行 `&` 与作业控制
- 命令查找依赖编译时写死的 `PATH_BIN` 目录（课程环境为 `/home/stu/class03/test15/mybin/`）
- 参数上限 `ARG_MAX 10`

以上限制是刻意保留的课程边界，后续迭代方向见 TODO。

## TODO

- [ ] 管道实现（`pipe` + `dup2`）
- [ ] 输入输出重定向
- [ ] 用 `PATH` 环境变量替代固定查找目录
