{
  description = "A flake for RE2 and related development tools";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (system:
      with import nixpkgs { inherit system; }; {
        devShells.default = mkShell {
          nativeBuildInputs = [ pkg-config gnumake llvm clang bazel python3 python311Packages.pybind11 python311Packages.absl-py python311Packages.matplotlib ];
          buildInputs = [ abseil-cpp gtest gbenchmark ];
          shellHook = ''
            export PATH="$PWD:$PATH"
          '';
        };
      });
}
