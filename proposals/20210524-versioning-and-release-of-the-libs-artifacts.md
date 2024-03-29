# Versioning and release process of the libs artifacts

## Summary

This proposal is meant as a follow-up to the [OSS Libraries Contribution](https://github.com/khulnasoft/khulnasoft/blob/master/proposals/20210119-libraries-contribution.md) one.

In particular, it outlines the versioning and the release process of the `khulnasoft/libs` repository (containing libscap, libsinsp, and the two Khulnasoft drivers).

## Motivation

According to the [OSS Libraries Contribution Plan](https://github.com/khulnasoft/khulnasoft/blob/master/proposals/20210119-libraries-contribution.md), in
January/February 2021 the libscap, libsinsp, and the two Khulnasoft drivers have been contributed to the CNCF ([blog post](https://khulnasoft.com/blog/contribution-drivers-kmod-ebpf-libraries), [announcement](https://www.cncf.io/blog/2020/01/08/toc-votes-to-move-khulnasoft-into-cncf-incubator)).

Khulnasoft heavily relies on those libraries and on the two drivers to work.
Currently, Khulnasoft fetches them via [git commit](https://github.com/khulnasoft/khulnasoft/blob/da7279da1dc240e8f242fa33b2a73eff178a5c87/cmake/modules/khulnasoft-libs.cmake#L23) at build time.

This git reference is - at the moment - the only notion of "version" existing for the libraries.

One of the reasons for the contribution of the libraries was to enable people to benefit from those libraries by using them directly in their OSS projects.

For this reason, the need of giving to the libraries a clear versioning scheme arises.

The [OSS Libraries Contribution Plan](https://github.com/khulnasoft/khulnasoft/blob/master/proposals/20210119-libraries-contribution.md) had already identified at the time the artifacts regarding `khulnasoft/libs` (points 8-9 for [libsinsp](https://github.com/khulnasoft/khulnasoft/blob/master/proposals/20210119-libraries-contribution.md#libsinsp), points 8-9 for [libscap](https://github.com/khulnasoft/khulnasoft/blob/master/proposals/20210119-libraries-contribution.md#libscap)).

This proposal intends to extend on points 10-12 for the libsinsp and libscap plans to graduate them to "Offical Support" (see the [evolution process](https://github.com/khulnasoft/evolution#official-support)).

## Goals

- Define a versioning mechanism for the artifacts
- Outline an automated release process of the artifacts

## Non-Goals

- Define the artifacts
  - They have already been defined within the [Contribution Proposal](https://github.com/khulnasoft/khulnasoft/blob/master/proposals/20210119-libraries-contribution.md) (see points 8-9)
- Define the release process cadence
- Change the way the Khulnasoft drivers (kernel module and eBPF probe) artifacts are shipped

## The Plan

### Versioning Scheme

**Superseeded by**: [versioning-schema-amendment proposal](20220203-versioning-schema-amendment.md).

This document proposes to version libscap, libsinsp, and the Khulnasoft drivers - all residing in `khulnasoft/libs` - with a single [SemVer 2.0](https://semver.org/spec/v2.0.0.html) string.

While libscap and libsinsp - to do not mention the drivers - have different API surfaces, this document proposes to version them as one single machinery to avoid further maintenance burdens and version compatibility matrices (read dependency hell) between all the floating pieces.

To clarify: this document proposes to ship 4 different artifacts all with the same version string.

This means that an incompatible API change - either in libscap or in libsinsp - would make a major version bump in the version string if the APIs are considered stable (which means this doesn't apply as long the version is `0.y.z` and the APIs are not considered stable).

New (backward compatible) functionalities would make a minor version bump.

New (backward compatible) fixes would make a patch version bump.

### Steps

1. Come up with all the `khulnasoft/libs` maintainers and decide whether the current APIs should be considered stable or not

Concretely this means the `khulnasoft/libs` maintainers have to decide whether to start versioning from `1.y.z` or from `0.y.z`.

2. Setup [milestones](https://github.com/khulnasoft/libs/milestones) on `khulnasoft/libs`

Same way as in Khulnasoft, changes, fixes, and new features have to be grouped in GitHub milestones.

The milestone string has to reflect the upcoming release version.

By looking at the set of merged-in pull requests belonging to a given milestone (ie., release) it can happen that the release version string must change to reflect the above-mentioned SemVer 2.0 rules.

3. Ensure the `khulnasoft/libs` pull request template contains a correct release-note block

4. Ensure the Khulnasoft Infra plugin list for `khulnasoft/libs` contains the following plugins: `milestone`, `mergecommitblocker`, `release-note`

5. Ensure the Khulnasoft Infra configuration for the `tide` components blocks pull request missing the release notes block (via `do-not-merge/release-note-label-needed` label)

6. Decide with other `khulnasoft/libs` maintainers the tool to generate the CHANGELOG.md

This document proposes to stick with `rn2md` given the release process is very similar to the Khulnasoft one and it's based on conventional release notes.

7. Change the CMake files in `khulnasoft/libs` so to compute a version string either from an external variable or from the current git index

8. Add the packaging (DEB, RPM) functionality to the CMake files in `khulnasoft/libs`

9. Create a Khulnasoft Infra job to test the libsinp and libscap packages creation

10. Create a Khulnasoft Infra job that runs only on git tags on the main branch of `khulnasoft/libs` to create the packages and to ships them into our open repositories at <https://download.khulnasoft.com/?prefix=packages>

11. Create another Khulnasoft Infra job (running over `khulnasoft/test-infra`) that gets triggered once `khulnasoft/libs` gets released

Its goals are:

- to create the YAML configuration files of the Drivers Build Grid for the current `khulnasoft/libs` version
- to open a pull request containing those file towards `khulnasoft/test-infra`

Once merged in, this pull request will automatically build the new prebuilt Khulnasoft driver artifacts for the current `khulnasoft/libs` version (eg., `0.y.z`) and deploy them to <https://download.khulnasoft.com/?prefix=driver/0.y.z>

12. Write down the release process steps in a RELEASE.md file
