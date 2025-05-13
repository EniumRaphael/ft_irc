{
	description = "Shell for ft_irc 42 project";

	inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
	inputs.flake-utils.url = "github:numtide/flake-utils";

	outputs = { self, nixpkgs, flake-utils }:
		flake-utils.lib.eachDefaultSystem (system:
			let
				pkgs = import nixpkgs {
					inherit system;
				};
			in {
				devShells.default = pkgs.mkShell {
					name = "irc-42";
					buildInputs = with pkgs; [
						clang
						clang-tools
						irssi
						tmux
					] ++ (
						if pkgs.stdenv.isLinux then [
							valgrind
						] else []
					);
					
					shellHook = ''
						export CXX=clang++
						export CXXFLAGS="-std=cpp98 -Wall -Werror -Wextra"
						printf "\n\033[0;90mCPP env loaded for: \033[38;5;220m${system}\033[0m\n"
					'';
					};
				}
		);
}
