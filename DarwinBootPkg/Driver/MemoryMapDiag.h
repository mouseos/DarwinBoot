// SPDX-License-Identifier: BSD-2-Clause-Patent
#ifndef DARWINBOOT_MEMORY_MAP_DIAG_H
#define DARWINBOOT_MEMORY_MAP_DIAG_H
#ifndef DARWINBOOT_MEMORY_MAP_DIAG
#define DARWINBOOT_MEMORY_MAP_DIAG 0
#endif

// Stack-only raw descriptor diagnostics. SerialPortWrite must not allocate or
// invoke boot services: this is also called between GetMemoryMap and EBS.
// Descriptor types/attributes are evidence only, never an ownership decision.
STATIC
VOID
DarwinDumpMemoryMap (UINTN Phase, CONST VOID *Map, UINTN Size, UINTN Stride)
{
#if DARWINBOOT_MEMORY_MAP_DIAG == 1
  CHAR8 Line[192];
  CONST CHAR8 *Stage = Phase == 0 ? "pre" : "final";
  UINTN Count, Limit, Index, Length;
  EFI_MEMORY_DESCRIPTOR Descriptor;

  if ((Stride < sizeof (Descriptor)) || (Size % Stride != 0) || ((Map == NULL) && (Size != 0)) || (Size > MAX_UINTN - (UINTN)Map)) {
    Length = AsciiSPrint (Line, sizeof (Line), "DBMM %a invalid bytes=%Lu stride=%Lu\r\n",
                         Stage, (UINT64)Size, (UINT64)Stride);
    SerialPortWrite ((UINT8 *)Line, Length);
    return;
  }
  Count = Size / Stride;
  Limit = Count < 1024 ? Count : 1024;
  Length = AsciiSPrint (Line, sizeof (Line), "DBMM %a count=%Lu bytes=%Lu stride=%Lu emitted=%Lu\r\n",
                       Stage, (UINT64)Count, (UINT64)Size, (UINT64)Stride, (UINT64)Limit);
  SerialPortWrite ((UINT8 *)Line, Length);
  for (Index = 0; Index < Limit; Index++) {
    // Copy only the standard descriptor; honor firmware's larger stride.
    // Index*Stride <= Size-Stride, so neither the product nor this read wraps.
    CopyMem (&Descriptor, (CONST UINT8 *)Map + Index * Stride, sizeof (Descriptor));
    Length = AsciiSPrint (Line, sizeof (Line),
                         "DBMM %a i=%Lu type=%u pa=%016Lx va=%016Lx pages=%016Lx attr=%016Lx\r\n",
                         Stage, (UINT64)Index, Descriptor.Type, Descriptor.PhysicalStart,
                         Descriptor.VirtualStart, Descriptor.NumberOfPages, Descriptor.Attribute);
    SerialPortWrite ((UINT8 *)Line, Length);
  }
  if (Limit != Count) {
    Length = AsciiSPrint (Line, sizeof (Line), "DBMM %a TRUNCATED remaining=%Lu\r\n", Stage, (UINT64)(Count - Limit));
    SerialPortWrite ((UINT8 *)Line, Length);
  }
#else
  (VOID)Phase; (VOID)Map; (VOID)Size; (VOID)Stride;
#endif
}
#endif
