make

./minishell 测试命令

valgrind --leak-check=full ./minishell 测试内存泄漏(readline本身有内存泄漏，可忽略)

重点命令：
1. sleep 5
	ctrl+\
	看有无打印错误信息
2. echo $USER $1ABC $"USER" "$USER"
3. cat << $USER
	$USER 或者 yopeng
4. export T="abc|123"
	echo $T


tester测试所有命令的方法：
1. 保证42-minishell-tester文件在Home或者minishell文件夹
2. 将注释的main放出来，注释掉简单版本的main
3. mstest m 测试所有命令
4. mstest vm 测试内存泄漏
5. mstest ne 测试无环境变量的情况

**注意
vosphere版本缺少：
1.ctrl+\ 打印错误
2.heredoc(cat << EOF)情况下tmp文件没有放在/tmp文件夹

github版本：
修复了以上两个缺陷
