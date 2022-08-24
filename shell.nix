let
  pinnedPkgs = import (builtins.fetchTarball {
    name = "nixos-22.05";
    url = "https://github.com/nixos/nixpkgs/archive/ce6aa13369b667ac2542593170993504932eb836.tar.gz";
    sha256 = "0d643wp3l77hv2pmg2fi7vyxn4rwy0iyr8djcw1h5x72315ck9ik";
  });
  
  pkgs = pinnedPkgs {};

  crossPkgs = pinnedPkgs {
    crossSystem = {
      config = "msp430-elf";
      libc = "newlib";
      gcc.float = " --enable-multilib --disable-libquadmath ";
    };
    overlays = [ (self: super: { gcc = self.gcc12; }) ];
  };

  python = pkgs.python39.withPackages(ps: with ps; [
    (buildPythonPackage rec {
       pname = "rtttl";
       version = "0.2";
       src = fetchPypi {
         inherit pname version;
         sha256 = "02h23mp9mvd9d7hsvj280k3drms9b1dbla4kar6m2fjdnhd9i9jq";
      };
    })
    pygobject3
    pyzmq
  ]);
  vscode = pkgs.vscode-with-extensions.override {
    vscode = pkgs.vscode;
    vscodeExtensions = [
      pkgs.vscode-extensions.bbenoist.nix
      pkgs.vscode-extensions.ms-vscode.cpptools
    ] ++ pkgs.vscode-utils.extensionsFromVscodeMarketplace [{
      name = "msp430-assembly";
      publisher = "zacharypenn";
      version = "1.0.0";
      sha256 = "1pjx57bsjkkly0110drhgxycx17m2hvgn5ppcawwsg0gg86k9v2a";
    }
    {
      name = "linkerscript";
      publisher = "zixuanwang";
      version = "1.0.2";
      sha256 = "0rr5mz8g8myskgixiw76rwda8g955a1al8kk4s30b0byfaszia17";
    }
    {
      name = "gnu-mapfiles";
      publisher = "trond-snekvik";
      version = "1.1.0";
      sha256 = "0416qprq9rnzl9na3fxhs9wnmws9zfm473qxnvji2vy752l4wxr4";
    }
    ];
  };
in
pkgs.mkShell {
  LD_LIBRARY_PATH = "${pkgs.mspds}/lib";
  shellHook = ''
    export LD_LIBRARY_PATH="${pkgs.mspds}/lib";
  '';
  nativeBuildInputs = with pkgs; [ crossPkgs.buildPackages.gcc crossPkgs.buildPackages.gdb mspds mspdebug zeromq python gnumake mbedtls pulseaudio pkgconfig gobject-introspection gtk3 lsof gdb vscode];
}