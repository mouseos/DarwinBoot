## SPDX-License-Identifier: BSD-2-Clause-Patent
# Include within [Components]. Only this module receives the optional defines.
!ifndef DARWINBOOT_MEMORY_MAP_DIAG
  DEFINE DARWINBOOT_MEMORY_MAP_DIAG = 0
!endif
!ifndef DARWINBOOT_BOARD_HANDOFF
  DEFINE DARWINBOOT_BOARD_HANDOFF = 0
!endif
DarwinBootPkg/Driver/DarwinBoot.inf {
  <BuildOptions>
    GCC:*_*_AARCH64_CC_FLAGS = -DDARWINBOOT_MEMORY_MAP_DIAG=$(DARWINBOOT_MEMORY_MAP_DIAG) -DDARWINBOOT_BOARD_HANDOFF=$(DARWINBOOT_BOARD_HANDOFF)
}
