{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ "bindings.cc" ],
      "include_dirs": [ "<(module_root_dir)/raylib-5.0_linux_amd64/include" ],
      "libraries": [
          "<(module_root_dir)/raylib-5.0_linux_amd64/lib/libraylib.a",
      ],
    }
  ]
}
