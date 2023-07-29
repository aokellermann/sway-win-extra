pkgname=sway-win-extra
pkgver=1.1.0
pkgrel=1
pkgdesc='Win10-like commands for swaywm workspaces.'
url='https://github.com/aokellermann/sway-win-extra'
arch=(x86_64)
depends=(swayipc-cpp nlohmann-json)
makedepends=(cmake git)
provides=("$pkgname")
conflicts=("$pkgname")
source=("git+$url")
sha256sums=(SKIP)

_cmake_flags=(
	-DCMAKE_BUILD_TYPE=Release
	-DCMAKE_INSTALL_LIBDIR=lib
	-DCMAKE_INSTALL_PREFIX=/usr
)

build() {
	mkdir build
	cd build
	cmake ../sway-win-extra "${_cmake_flags[@]}" -DBUILD_SHARED_LIBS=ON
	make
}

package() {
	cd build
	make "DESTDIR=$pkgdir" install
}