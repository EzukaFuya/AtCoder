#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

# コンパイル
gcc $1.cpp -o ./build/$1

if [ $? -ne 0 ]; then
    echo -e "${RED}コンパイルエラー${NC}"
    exit 1
fi

test_num=0
state=""
input=""
expected=""

while IFS= read -r line || [ -n "$line" ]; do
    if [[ $line =~ ^#.*$ ]] || [[ -z "${line// }" ]]; then
        continue
    fi

    if [[ $line == "[input]" ]]; then
        if [ ! -z "$input" ]; then
            ((test_num++))
            echo "== テストケース ${test_num} =="
            echo "入力:"
            echo "$input"
            echo "出力:"
            # 改行を削除して比較
            actual=$(echo "$input" | ./build/$1 | tr -d '\n')
            expected_trim=$(echo "$expected" | tr -d '\n')
            echo "$actual"
            
            if [ "$actual" = "$expected_trim" ]; then
                echo -e "${GREEN}OK${NC}"
            else
                echo -e "${RED}NG${NC}"
                echo "期待される出力:"
                echo "$expected"
            fi
            echo "-------------------"
            input=""
            expected=""
        fi
        state="input"
        continue
    fi

    if [[ $line == "[expected]" ]]; then
        state="expected"
        continue
    fi

    if [ "$state" == "input" ]; then
        input="${input}${line}"$'\n'
    elif [ "$state" == "expected" ]; then
        expected="${expected}${line}"$'\n'
    fi
done < test_$1.txt

# 最後のテストケースを処理
if [ ! -z "$input" ]; then
    ((test_num++))
    echo "== テストケース ${test_num} =="
    echo "入力:"
    echo "$input"
    echo "出力:"
    actual=$(echo "$input" | ./build/$1 | tr -d '\n')
    expected_trim=$(echo "$expected" | tr -d '\n')
    echo "$actual"
    if [ "$actual" = "$expected_trim" ]; then
        echo -e "${GREEN}OK${NC}"
    else
        echo -e "${RED}NG${NC}"
        echo "期待される出力:"
        echo "$expected"
    fi
    echo "-------------------"
fi