# プログラム名とオブジェクトファイル名
PROGRAM = yahtzee

# ソースコード、出力ディレクトリ、ヘッダーディレクトリ
SRC_DIR = src
BIN_DIR = bin
BUILD_DIR = build
INCLUDE_DIR = include

# ソースファイルからオブジェクトファイルのリストを生成
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

CC = gcc
CFLAGS = -Wall -I$(INCLUDE_DIR)

LDFLAGS = -lncursesw

TARGET = $(BIN_DIR)/$(PROGRAM)
# すべてのビルドターゲット
all: $(TARGET)

# 実行ファイルの生成
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

# オブジェクトファイルの生成ルール (buildフォルダに出力)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# binディレクトリが存在しない場合は作成
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# buildディレクトリが存在しない場合は作成
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# 実行ターゲット
.PHONY: run
run: $(BIN_DIR)/$(PROGRAM)
	$(BIN_DIR)/$(PROGRAM)

# クリーンアップ
.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS)
