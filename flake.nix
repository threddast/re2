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
          nativeBuildInputs = [ pkg-config gnumake ];
          buildInputs = [ abseil-cpp gtest gbenchmark ];
          shellHook = ''
            export PATH="$PWD:$PATH"
          '';
        };
      });
}
