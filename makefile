# компиляторы
CC := gcc
CCPP := g++
RC := windres

# пути
INC := app\inc
SRC := app\src
RSRC := app\rsrc
LA_INC := LA\inc
LA_SRC := LA\src
WINAPI_INC := WINAPI\inc
WINAPI_SRC := WINAPI\src
OUT := out
OUT_R := $(OUT)\Release
OUT_D := $(OUT)\Debug

# флаги
CFLAGS := -std=c99 -Wall -Wextra -Wpedantic -DUNICODE -D_UNICODE
CPPFLAGS := -std=c++11 -Wall -Wextra -Wpedantic -DUNICODE -D_UNICODE
RSRCFLAGS := -I$(INC)

# условная сборка
mode := release

ifeq ($(mode), release)
	CFLAGS += -DNDEBUG -g0 -o3
	CPPFLAGS += -DNDEBUG -g0 -o3
	OUT := $(OUT_R)
endif

ifeq ($(mode), debug)
	CFLAGS += -D_DEBUG -g3
	CPPFLAGS += -D_DEBUG -g3
	OUT := $(OUT_D)
endif

# перечисление исходные файлов начало =====================================================

# перечисление исходных файлов приложения
APP_FILES := $(wildcard $(SRC)/*.cpp)

# перечисление исходных файлов библиотеки LA
LA_FILES := $(wildcard $(LA_SRC)/*.c)

# перечисление исходных файлов библиотеки WINAPI
WINAPI_FILES := $(wildcard $(WINAPI_SRC)/*.cpp)

# перечисление исходные файлов конец ======================================================

# файлы приложения начало =================================================================

# файлы основного приложения 
APP_OBJ := $(patsubst $(SRC)/%.cpp,$(OUT)/%.o,$(filter %.cpp,$(APP_FILES)))

# файлы библиотеки линейной алгебры
LA_OBJ := $(patsubst $(LA_SRC)/%.c,$(OUT)/%.o,$(filter %.c,$(LA_FILES)))

# файлы библиотеки WINAPI
WINAPI_OBJ := $(patsubst $(WINAPI_SRC)/%.cpp,$(OUT)/%.o,$(filter %.cpp,$(WINAPI_FILES)))

# файлы приложения конец ==================================================================

# Сборка начало ===========================================================================

# линковка программы (порядок библиотек имеет значение)
app.exe : $(APP_OBJ) $(OUT)/resource.o WINAPI.lib LA.lib
	$(CCPP) -mwindows -o $@ $^ -lgdi32

# линковка библиотеки
LA.lib : $(LA_OBJ)
	ar rcs $@ $^
	ranlib $@

# линковка библиотеки
WINAPI.lib : $(WINAPI_OBJ) LA.lib
	ar rcs $@ $^
	ranlib $@

# Сборка конец ===========================================================================

# Компоновка начало =======================================================================

# компиляция файлов основной программы
$(APP_OBJ) : $(OUT)/%.o : $(SRC)/%.cpp | out_folder
	$(CCPP) $(CPPFLAGS) -I$(INC) -I$(LA_INC) -I$(WINAPI_INC) -c $< -o $@

# компиляция библиотеки
$(LA_OBJ) : $(OUT)/%.o : $(LA_SRC)/%.c | out_folder
	$(CC) $(CFLAGS) -I$(LA_INC) -c $< -o $@

# компиляция библиотеки
$(WINAPI_OBJ) : $(OUT)/%.o : $(WINAPI_SRC)/%.cpp | out_folder
	$(CCPP) $(CPPFLAGS) -I$(LA_INC) -I$(WINAPI_INC) -c $< -o $@

# компиляция скриптового ресурса
$(OUT)/resource.o : $(RSRC)/resource.rc | out_folder
	$(RC) $(RSRCFLAGS) -o $@ $<

# Компоновка конец =======================================================================

# Создать папку для объектников
.PHONY: out_folder
out_folder:
	@if not exist "$(OUT)" mkdir "$(OUT)"
	@if not exist "$(OUT_D)" mkdir "$(OUT_D)"
	@if not exist "$(OUT_R)" mkdir "$(OUT_R)"

.PHONY: clean
clean:
	@if exist "$(OUT)" rd /s /q $(OUT)
	@if exist ".\*.exe" del /q .\*.exe
	@if exist ".\*dll" del /q .\*dll
	@if exist ".\*lib" del /q .\*lib
