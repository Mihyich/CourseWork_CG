# компиляторы
CC := gcc
CCPP := g++
RC := windres

# пути
APP_INC := app/inc
APP_SRC := app/src
APP_RSRC := app/rsrc

GLSL_INC := GLSL/inc
GLSL_SRC := GLSL/src

SM_INC := ShadowMap/inc
SM_SRC := ShadowMap/src

RT_INC := RayTracing/inc
RT_SRC := RayTracing/src

LA_INC := LA/inc
LA_SRC := LA/src

WINAPI_INC := WINAPI/inc
WINAPI_SRC := WINAPI/src

ASSIMP_INC := C:/assimp/include

OUT := out
OUT_R := $(OUT)/Release
OUT_D := $(OUT)/Debug

# флаги
CFLAGS := -std=c99 -Wall -Wextra -Wpedantic -DUNICODE -D_UNICODE
CPPFLAGS := -std=c++14 -Wall -Wextra -Wpedantic -DUNICODE -D_UNICODE
RSRCFLAGS := -I$(APP_INC)

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
APP_FILES := $(wildcard $(APP_SRC)/*.cpp)

# перечисление исходных файлов библиотеки GLSL
GLSL_FILES := $(wildcard $(GLSL_SRC)/*.cpp)

# перечисление исходных файлов библиотеки ShadowMap
SM_FILES := $(wildcard $(SM_SRC)/*.cpp)

# перечисление исходных файлов библиотеки RayTracing
RT_FILES := $(wildcard $(RT_SRC)/*.cpp)

# перечисление исходных файлов библиотеки LA
LA_FILES := $(wildcard $(LA_SRC)/*.c)

# перечисление исходных файлов библиотеки WINAPI
WINAPI_FILES := $(wildcard $(WINAPI_SRC)/*.cpp)

# перечисление исходные файлов конец ======================================================

# файлы приложения начало =================================================================

# файлы основного приложения 
APP_OBJ := $(patsubst $(APP_SRC)/%.cpp,$(OUT)/%.o,$(filter %.cpp,$(APP_FILES)))

# файлы библиотеки GLSL
GLSL_OBJ := $(patsubst $(GLSL_SRC)/%.cpp,$(OUT)/%.o,$(filter %.cpp,$(GLSL_FILES)))

# файлы библиотеки ShadowMap
SM_OBJ := $(patsubst $(SM_SRC)/%.cpp,$(OUT)/%.o,$(filter %.cpp,$(SM_FILES)))

# файлы библиотеки RayTracing
RT_OBJ := $(patsubst $(RT_SRC)/%.cpp,$(OUT)/%.o,$(filter %.cpp,$(RT_FILES)))

# файлы библиотеки линейной алгебры
LA_OBJ := $(patsubst $(LA_SRC)/%.c,$(OUT)/%.o,$(filter %.c,$(LA_FILES)))

# файлы библиотеки WINAPI
WINAPI_OBJ := $(patsubst $(WINAPI_SRC)/%.cpp,$(OUT)/%.o,$(filter %.cpp,$(WINAPI_FILES)))

# файлы приложения конец ==================================================================

# Сборка начало ===========================================================================

# линковка программы (порядок библиотек имеет значение)
app.exe : $(APP_OBJ) $(OUT)/resource.o WINAPI.lib LA.lib GLSL.lib ShadowMap.lib RayTracing.lib
	$(CCPP) -mwindows -o $@ $^ -lgdi32 -ldwmapi -lopengl32 -Lc:/assimp/build/bin -lassimp-5

# линковка библиотеки GLSL
GLSL.lib : $(GLSL_OBJ)
	ar rcs $@ $^
	ranlib $@

# линковка библиотеки ShadoMap
ShadowMap.lib : $(SM_OBJ)
	ar rcs $@ $^
	ranlib $@

# линковка библиотеки RayTracing
RayTracing.lib : $(RT_OBJ)
	ar rcs $@ $^
	ranlib $@

# линковка библиотеки линейной алгебры
LA.lib : $(LA_OBJ)
	ar rcs $@ $^
	ranlib $@

# линковка библиотеки Winapi
WINAPI.lib : $(WINAPI_OBJ)
	ar rcs $@ $^
	ranlib $@

# Сборка конец ===========================================================================

# Компоновка начало =======================================================================

# компиляция файлов основной программы
$(APP_OBJ) : $(OUT)/%.o : $(APP_SRC)/%.cpp | out_folder
	$(CCPP) $(CPPFLAGS) -I$(APP_INC) -I$(GLSL_INC) -I$(SM_INC) -I$(RT_INC) -I$(LA_INC) -I$(WINAPI_INC) -I$(ASSIMP_INC) -c $< -o $@

# компиляция библиотеки GLSL
$(GLSL_OBJ) : $(OUT)/%.o : $(GLSL_SRC)/%.cpp | out_folder
	$(CCPP) $(CPPFLAGS) -I$(GLSL_INC) -I$(LA_INC) -I$(WINAPI_INC) -c $< -o $@

# компиляция библиотеки ShadowMap
$(SM_OBJ) : $(OUT)/%.o : $(SM_SRC)/%.cpp | out_folder
	$(CCPP) $(CPPFLAGS) -I$(SM_INC) -I$(GLSL_INC) -I$(LA_INC) -I$(WINAPI_INC) -c $< -o $@

# компиляция библиотеки RayTracing
$(RT_OBJ) : $(OUT)/%.o : $(RT_SRC)/%.cpp | out_folder
	$(CCPP) $(CPPFLAGS) -I$(RT_INC) -I$(GLSL_INC) -I$(LA_INC) -I$(WINAPI_INC) -c $< -o $@

# компиляция библиотеки линейной алгебры
$(LA_OBJ) : $(OUT)/%.o : $(LA_SRC)/%.c | out_folder
	$(CC) $(CFLAGS) -I$(LA_INC) -c $< -o $@

# компиляция библиотеки Winapi
$(WINAPI_OBJ) : $(OUT)/%.o : $(WINAPI_SRC)/%.cpp | out_folder
	$(CCPP) $(CPPFLAGS) -I$(WINAPI_INC) -c $< -o $@

# компиляция скриптового ресурса
$(OUT)/resource.o : $(APP_RSRC)/resource.rc | out_folder
	$(RC) $(RSRCFLAGS) -o $@ $<

# Компоновка конец =======================================================================

# Создать папку для объектников
out_folder:
	@if not exist "$(OUT)" mkdir "$(OUT)"
	@if not exist "$(OUT_D)" mkdir "$(OUT_D)"
	@if not exist "$(OUT_R)" mkdir "$(OUT_R)"
.PHONY: out_folder

clean:
	@if exist "$(OUT)" rd /s /q $(OUT)
	@if exist ".\*.exe" del /q .\*.exe
	@if exist ".\*dll" del /q .\*dll
	@if exist ".\*lib" del /q .\*lib
.PHONY: clean
