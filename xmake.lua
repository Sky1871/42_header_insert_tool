set_project("HIT")
set_version("0.1.0")
set_languages("c++23")
set_toolchains("clang")

add_rules("mode.debug", "mode.release")

set_warnings("all", "extra")
add_cxxflags("-Wpedantic", "-Wconversion", "-Wshadow", { tools = { "gcc", "clang" } })

target("HIT")
set_kind("static")
add_files("srcs/*.cpp", { public = true })
add_includedirs("includes", { public = true })
add_headerfiles("includes/(*.hpp)")
