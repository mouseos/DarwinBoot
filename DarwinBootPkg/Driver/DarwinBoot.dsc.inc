## SPDX-License-Identifier: BSD-2-Clause-Patent
# Include within [Components]. Only this module receives the optional define.
DarwinBootPkg/Driver/DarwinBoot.inf {
!ifdef DARWINBOOT_MEMORY_MAP_DIAG
  <BuildOptions>
    GCC:*_*_AARCH64_CC_FLAGS = -DDARWINBOOT_MEMORY_MAP_DIAG=$(DARWINBOOT_MEMORY_MAP_DIAG)
!endif
}
