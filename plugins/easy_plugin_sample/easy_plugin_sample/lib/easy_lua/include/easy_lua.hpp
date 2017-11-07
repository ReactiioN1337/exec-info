///-------------------------------------------------------------------------------------------------
/// Author:             ReactiioN
/// Created:            03.10.2017
/// 
/// Last modified by:   ReactiioN
/// Last modified on:   10.10.2017
///-------------------------------------------------------------------------------------------------
///     Copyright (c) ReactiioN <https://reactiion.net>. All rights reserved.
///-------------------------------------------------------------------------------------------------
///                              __
///    ___  ____ ________  __   / /_  ______ _
///   / _ \/ __ `/ ___/ / / /  / / / / / __ `/
///  /  __/ /_/ (__  ) /_/ /  / / /_/ / /_/ /
///  \___/\__,_/____/\__, /  /_/\__,_/\__,_/
///                 /____/
/// 
/// # Author: ReactiioN
/// # Timestamp: 10.16.2017
/// # https://github.com/ReactiioN1337/exec-info
/// # supported lua version: 5.3.3
///-------------------------------------------------------------------------------------------------
/// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
/// Copyright (c) 2017 ReactiioN <https://reactiion.net>.
///
/// Permission is hereby  granted, free of charge, to any  person obtaining a copy
/// of this software and associated  documentation files (the "Software"), to deal
/// in the Software  without restriction, including without  limitation the rights
/// to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
/// copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
/// furnished to do so, subject to the following conditions:
/// The above copyright notice and this permission notice shall be included in all
/// copies or substantial portions of the Software.
/// THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
/// IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
/// FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
/// AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
/// LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.
///-------------------------------------------------------------------------------------------------
#pragma once
/// <reference>
/// http://en.cppreference.com/w/cpp/header/string
/// </reference>
#include <string>
/// <reference>
/// http://en.cppreference.com/w/cpp/header/vector
/// </reference>
#include <vector>
/// <reference>
/// https://www.lua.org/manual/5.1/
/// http://luajit.org/
/// </reference>
#include "luajit/lua.hpp"
/// <reference (by c42f)>
/// https://github.com/c42f/tinyformat
/// </reference>
#include "contrib/tinyformat.hpp"
/// <reference (by frk)>
/// https://www.unknowncheats.me/forum/c-and-c-/164273-xor-compile-time.html
/// </reference>
#include "contrib/xorstr.hpp"

#if !defined(EASY_LUA_MSG)
#define EASY_LUA_MSG(s, ...) tfm::printf(XORS("[easy_lua] ")); \
                             tfm::printfln(XORS(s), __VA_ARGS__)
#endif

#if !defined(EASY_LUA_CAST_LUA)
#define EASY_LUA_CAST_LUA(ptr)  (lua_State*)ptr
#endif

#if !defined(EASY_LUA_CAST_EASY)
#define EASY_LUA_CAST_EASY(ptr) (easy_lua*)ptr
#endif

#if !defined(EASY_LUA_MAKE_PLUGIN)
#define EASY_LUA_MAKE_PLUGIN(onPluginLoad, onPluginUnload) extern "C" {\
    __declspec(dllexport) bool plugin_load( easy_lua* lua )            \
    {                                                                  \
        return onPluginLoad( lua );                                    \
    }                                                                  \
    __declspec(dllexport) void plugin_unload()                         \
    {                                                                  \
        onPluginUnload();                                              \
    }                                                                  \
}
#endif

class easy_lua
{
public:
    enum EState : uint8_t
    {
        /// <summary> 
        /// An enum constant representing the state success option. 
        /// </summary>
        State_Success = 0,
        /// <summary> 
        /// An enum constant representing the state runtime option. 
        /// </summary>
        State_Runtime,
        /// <summary> 
        /// An enum constant representing the state syntax option. 
        /// </summary>
        State_Syntax,
        /// <summary> 
        /// An enum constant representing the state Memory Allocate option. 
        /// </summary>
        State_MemAlloc,
        /// <summary> 
        /// An enum constant representing the state Error handling option. 
        /// </summary>
        State_ErrHandling,
    };

    /// <summary> 
    /// The load plugin callback typedef.
    /// </summary>
    using FnLoadPlugin   = bool( *)( easy_lua* );

    /// <summary> 
    /// The unload plugin callback typedef.
    /// </summary>
    using FnUnloadPlugin = void( *)();

private:
    /// <summary> 
    /// The callback function typedef. 
    /// </summary>
    using FnCallback = int32_t( *)( easy_lua* );

public:
    typedef struct LuaCFunc
    {
        /// <summary>
        /// The function name. </summary>
        const char* name;

        /// <summary> 
        /// The callback function.
        /// </summary>
        FnCallback  callback;
    }LuaCFunc;

protected:
    easy_lua() = default;

public:
    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Initializes this object. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <param name="include_directory">    Pathname of the include directory. </param>
    ///
    /// <returns>   Null if it fails, else a pointer to an easy_lua. </returns>
    ///-------------------------------------------------------------------------------------------------
    static easy_lua* initialize(
        const std::string& include_directory );

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Shared the given object. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <param name="obj">  [in,out] (Optional) If non-null, the object. </param>
    ///
    /// <returns>   Null if it fails, else a pointer to an easy_lua. </returns>
    ///-------------------------------------------------------------------------------------------------
    static easy_lua* shared(
        void* obj = nullptr );

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Closes the given lua. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <param name="lua">  [in,out] If non-null, the lua. </param>
    ///-------------------------------------------------------------------------------------------------
    static void close(
        easy_lua** lua );

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Gets a version. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <param name="release">  [in,out] If non-null, the release. </param>
    /// <param name="major">    [in,out] If non-null, the major. </param>
    /// <param name="minor">    [in,out] If non-null, the minor. </param>
    /// <param name="build">    [in,out] If non-null, the build. </param>
    ///-------------------------------------------------------------------------------------------------
    static void get_version(
        uint32_t* release,
        uint32_t* major,
        uint32_t* minor,
        uint32_t* build );

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Executes. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <param name="script">       The script. </param>
    /// <param name="from_memory">  (Optional) True to from memory. </param>
    ///
    /// <returns>   True if it succeeds, false if it fails. </returns>
    ///-------------------------------------------------------------------------------------------------
    bool execute(
        const std::string& script,
        const bool         from_memory = false ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Query if 'stackpos' is bool. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <param name="stackpos"> The stackpos. </param>
    ///
    /// <returns>   True if bool, false if not. </returns>
    ///-------------------------------------------------------------------------------------------------
    bool is_bool(
        const int32_t stackpos ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Query if 'stackpos' is number. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <param name="stackpos"> The stackpos. </param>
    ///
    /// <returns>   True if number, false if not. </returns>
    ///-------------------------------------------------------------------------------------------------
    bool is_number(
        const int32_t stackpos ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Query if 'stackpos' is string. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <param name="stackpos"> The stackpos. </param>
    ///
    /// <returns>   True if string, false if not. </returns>
    ///-------------------------------------------------------------------------------------------------
    bool is_string(
        const int32_t stackpos ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Query if 'stackpos' is userdata. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <param name="stackpos"> The stackpos. </param>
    ///
    /// <returns>   True if userdata, false if not. </returns>
    ///-------------------------------------------------------------------------------------------------
    bool is_userdata(
        const int32_t stackpos ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Query if 'stackpos' is nil. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <param name="stackpos"> The stackpos. </param>
    ///
    /// <returns>   True if nil, false if not. </returns>
    ///-------------------------------------------------------------------------------------------------
    bool is_nil(
        const int32_t stackpos ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Gets a bool. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <param name="stackpos">         The stackpos. </param>
    /// <param name="default_value">    (Optional) True to default value. </param>
    /// <param name="pop_value">        (Optional) True to pop value. </param>
    ///
    /// <returns>   True if it succeeds, false if it fails. </returns>
    ///-------------------------------------------------------------------------------------------------
    bool get_bool(
        const int32_t stackpos,
        const bool default_value = false,
        const bool pop_value = false ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Gets a string. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <param name="stackpos"> The stackpos. </param>
    ///
    /// <returns>   Null if it fails, else the string. </returns>
    ///-------------------------------------------------------------------------------------------------
    const char* get_string(
        const int32_t stackpos ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Loads a file. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <param name="file"> The file. </param>
    ///
    /// <returns>   The file. </returns>
    ///-------------------------------------------------------------------------------------------------
    EState load_file(
        const std::string& file ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Pcalls. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <param name="num_args">         Number of arguments. </param>
    /// <param name="num_results">      Number of results. </param>
    /// <param name="error_function">   The error function. </param>
    ///
    /// <returns>   An EState. </returns>
    ///-------------------------------------------------------------------------------------------------
    EState pcall(
        const int32_t num_args,
        const int32_t num_results,
        const int32_t error_function ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Tops the given needed. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <param name="needed">   The needed. </param>
    ///
    /// <returns>   True if it succeeds, false if it fails. </returns>
    ///-------------------------------------------------------------------------------------------------
    bool top(
        const size_t needed ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Tops. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <param name="mins"> The mins. </param>
    /// <param name="maxs"> The maxs. </param>
    ///
    /// <returns>   True if it succeeds, false if it fails. </returns>
    ///-------------------------------------------------------------------------------------------------
    bool top(
        const size_t mins,
        const size_t maxs ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Export class. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <param name="global_name">      Name of the global. </param>
    /// <param name="metatable_name">   Name of the metatable. </param>
    /// <param name="functions">        The functions. </param>
    ///
    /// <returns>   Null if it fails, else a pointer to a const easy_lua. </returns>
    ///-------------------------------------------------------------------------------------------------
    const easy_lua* export_class(
        const std::string&    global_name,
        const std::string&    metatable_name,
        std::vector<LuaCFunc> functions ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Export a C function. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <param name="name">     The name. </param>
    /// <param name="callback"> The callback. </param>
    ///
    /// <returns>   Null if it fails, else a pointer to a const easy_lua. </returns>
    ///-------------------------------------------------------------------------------------------------
    const easy_lua* export_function(
        const std::string& name,
        FnCallback         callback ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Gets a global. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <param name="name"> The name. </param>
    ///
    /// <returns>   Null if it fails, else the global. </returns>
    ///-------------------------------------------------------------------------------------------------
    const easy_lua* get_global(
        const std::string& name ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Sets a global. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <param name="name"> The name. </param>
    ///
    /// <returns>   Null if it fails, else a pointer to a const easy_lua. </returns>
    ///-------------------------------------------------------------------------------------------------
    const easy_lua* set_global(
        const std::string& name ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Removes 'num_elements' from the top-of-stack and returns this object. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <param name="num_elements"> The Number elements to pop. </param>
    ///
    /// <returns>   Null if it fails, else this object. </returns>
    ///-------------------------------------------------------------------------------------------------
    const easy_lua* pop(
        const int32_t num_elements ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Removes the top-of-stack and returns this object. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <returns>   Null if it fails, else this object. </returns>
    ///-------------------------------------------------------------------------------------------------
    const easy_lua* pop_top() const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Pushes a bool. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <param name="value">    True to value. </param>
    ///
    /// <returns>   Null if it fails, else a pointer to a const easy_lua. </returns>
    ///-------------------------------------------------------------------------------------------------
    const easy_lua* push_bool(
        const bool value ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Pushes a string. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <param name="str">  The string. </param>
    ///
    /// <returns>   Null if it fails, else a pointer to a const easy_lua. </returns>
    ///-------------------------------------------------------------------------------------------------
    const easy_lua* push_string(
        const std::string& str ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Pushes the nil. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <returns>   Null if it fails, else a pointer to a const easy_lua. </returns>
    ///-------------------------------------------------------------------------------------------------
    const easy_lua* push_nil() const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Destroys the userdata. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <param name="stackpos"> The stackpos. </param>
    /// <param name="name">     The name. </param>
    ///
    /// <returns>   An int32_t. </returns>
    ///-------------------------------------------------------------------------------------------------
    int32_t destroy_userdata(
        const int32_t      stackpos,
        const std::string& name ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Pushed the given value. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <param name="val">  The value. </param>
    ///
    /// <returns>   An int32_t. </returns>
    ///-------------------------------------------------------------------------------------------------
    int32_t pushed(
        const int32_t val ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Gets the top. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <returns>   An int32_t. </returns>
    ///-------------------------------------------------------------------------------------------------
    int32_t top() const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Closes this object. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///-------------------------------------------------------------------------------------------------
    void close();

public:
    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Creates a new userdata. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <typeparam name="T">    Generic type parameter. </typeparam>
    ///
    /// <returns>   Null if it fails, else a handle to a T. </returns>
    ///-------------------------------------------------------------------------------------------------
    template<typename T>
    T** new_userdata() const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Pushes a number. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <typeparam name="T">    Generic type parameter. </typeparam>
    /// <param name="value">    The value. </param>
    ///
    /// <returns>   Null if it fails, else a pointer to a const easy_lua. </returns>
    ///-------------------------------------------------------------------------------------------------
    template<typename T>
    const easy_lua* push_number(
        const T value ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Pushes an integer. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <typeparam name="T">    Generic type parameter. </typeparam>
    /// <param name="value">    The value. </param>
    ///
    /// <returns>   Null if it fails, else a pointer to a const easy_lua. </returns>
    ///-------------------------------------------------------------------------------------------------
    template<typename T>
    const easy_lua* push_integer(
        const T value ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Pushes an userdata. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <typeparam name="T">    Generic type parameter. </typeparam>
    /// <param name="name"> The name. </param>
    /// <param name="data"> [in,out] If non-null, the data. </param>
    ///
    /// <returns>   Null if it fails, else a pointer to a const easy_lua. </returns>
    ///-------------------------------------------------------------------------------------------------
    template<typename T>
    const easy_lua* push_userdata(
        const std::string& name,
        T*                 data ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Gets a number. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <typeparam name="T">    Generic type parameter. </typeparam>
    /// <param name="stackpos">         The stackpos. </param>
    /// <param name="default_value">    (Optional) The default value. </param>
    /// <param name="pop_value">        (Optional) True to pop value. </param>
    ///
    /// <returns>   The number. </returns>
    ///-------------------------------------------------------------------------------------------------
    template<typename T = lua_Number>
    T get_number(
        const int32_t stackpos,
        const T       default_value = static_cast<T>( 0 ),
        const bool    pop_value = false ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Gets an integer from stack. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <typeparam name="T">    Generic type parameter. </typeparam>
    /// <param name="stackpos">         The stackpos. </param>
    /// <param name="default_value">    (Optional) The default value. </param>
    /// <param name="pop_value">        (Optional) True to pop value. </param>
    ///
    /// <returns>   The integer. </returns>
    ///-------------------------------------------------------------------------------------------------
    template<typename T = lua_Integer>
    T get_integer(
        const int32_t stackpos,
        const T       default_value = static_cast<T>( 0 ),
        const bool    pop_value = false ) const;

    ///-------------------------------------------------------------------------------------------------
    /// <summary>   Gets an userdata. </summary>
    ///
    /// <remarks>   ReactiioN, 03.10.2017. </remarks>
    ///
    /// <typeparam name="T">    Generic type parameter. </typeparam>
    /// <param name="stackpos">     The stackpos. </param>
    /// <param name="name">         The name. </param>
    /// <param name="pop_value">    (Optional) True to pop value. </param>
    ///
    /// <returns>   Null if it fails, else the userdata. </returns>
    ///-------------------------------------------------------------------------------------------------
    template<typename T>
    T* get_userdata(
        const int32_t      stackpos,
        const std::string& name,
        const bool         pop_value = false ) const;
};

template<typename T>
T** easy_lua::new_userdata() const
{
    return reinterpret_cast<T**>(
        lua_newuserdata( EASY_LUA_CAST_LUA( this ), sizeof( T* ) )
    );
}

template<typename T>
const easy_lua* easy_lua::push_number(
    const T value ) const
{
    static_assert( std::is_arithmetic<T>::value, "Type T has to be arithmetic" );
    lua_pushnumber( EASY_LUA_CAST_LUA( this ), static_cast<lua_Number>( value ) );
    return this;
}

template<typename T>
const easy_lua* easy_lua::push_integer(
    const T value ) const
{
    static_assert( std::is_arithmetic<T>::value, "Type T has to be arithmetic" );
    lua_pushinteger( EASY_LUA_CAST_LUA( this ), static_cast<lua_Integer>( value ) );
    return this;
}

template<typename T>
const easy_lua* easy_lua::push_userdata(
    const std::string& name,
    T*                 data ) const
{
    if( !name.empty() && data ) {
        auto created_data = new_userdata<T>();
        if( created_data ) {
            *created_data = data;
            luaL_getmetatable( EASY_LUA_CAST_LUA( this ), name.c_str() );
            lua_setmetatable( EASY_LUA_CAST_LUA( this ), -2 );
            return this;
        }
    }
    return nullptr;
}

template<typename T>
T easy_lua::get_number(
    const int32_t stackpos,
    const T       default_value,
    const bool    pop_value ) const
{
    if( is_number( stackpos ) ) {
        auto n = static_cast<T>( lua_tonumber( EASY_LUA_CAST_LUA( this ), stackpos ) );
        if( pop_value ) {
            pop( 1 );
        }
        return n;
    }
    return default_value;
}

template<typename T>
T easy_lua::get_integer(
    const int32_t stackpos,
    const T       default_value,
    const bool    pop_value ) const
{
    if( is_number( stackpos ) ) {
        auto i = static_cast<T>( lua_tointeger( EASY_LUA_CAST_LUA( this ), stackpos ) );
        if( pop_value ) {
            pop( 1 );
        }
        return i;
    }
    return default_value;
}

template<typename T>
T* easy_lua::get_userdata(
    const int32_t      stackpos,
    const std::string& name,
    const bool         pop_value ) const
{
    if( is_userdata( stackpos ) && !name.empty() ) {
        auto v = luaL_checkudata(
            EASY_LUA_CAST_LUA( this ),
            stackpos,
            name.data()
        );
        if( v ) {
            if( pop_value ) {
                pop( 1 );
            }
            return *reinterpret_cast<T**>( v );
        }
    }
    return nullptr;
}
