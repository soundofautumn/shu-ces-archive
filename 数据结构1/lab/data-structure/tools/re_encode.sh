#!/bin/sh

# 获取文件
# 可以将ls替换为find精确查找文件
files=`find ${PWD} -type f`

# 当前脚本文件
current_file=${PWD}/re_encode.sh

echo "current file: ${current_file}"
echo "re-encode file list:"

for f in ${files}
do
    if [ ${f} != ${current_file} ]
    then
        echo "${f}"

        # iconv -f 原始文件格式 -t 转换格式 <文件>
        iconv -f GBK -t UTF-8 "${f}" > "$f.utf8encode"

        rm -f "${f}"
    fi
done

# 已编码文件
encode_files=`find $PWD -type f -name "*.utf8encode"`

for f in ${encode_files}
do
   new_name=`echo $f | sed "s/.utf8encode//g"`
   mv "${f}" "${new_name}"
done

echo "re-encode OK :-)"