# Home of Khulnasoft Drivers Syscalls Report

Thanks to our [syscalls-bumper](https://github.com/khulnasoft/syscalls-bumper) project, we can consistently support the latest syscalls added to the Linux kernel.

Our automation adds new syscalls as generic events, meaning we don't extract the syscall arguments. Instead, we solely monitor when the syscall occurs. If necessary, developers can create new parsers to extract and make available each syscall argument. Internally, we refer to the extractors on the kernel side as "fillers". This process also involves the creation of a new event type in libsinsp.

## Glossary

The Khulnasoft Projects' kernel drivers support monitoring a range of syscalls. For a subset of syscalls (indicated with 🟡), we only monitor when the syscalls occur (internally in libs, we refer to these as generic syscalls), but we do not extract the syscall arguments.

On the other hand, syscalls indicated with 🟢 in the report are fully monitored. This means we read and parse each syscall argument. You can learn more about the specific syscall arguments for these syscalls by referring to the libs' [event_table](https://github.com/khulnasoft/libs/blob/master/driver/event_table.c) or the official Linux man pages.

* 🟢 → syscall is implemented as dedicated libsinsp event type and each argument of the syscall is extracted and parsed.
* 🟡 → syscall is implemented as a generic event; we only monitor when the syscall occurs.

Navigate to the Report on the left, or click this [link](report.md).
