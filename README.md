# Prostredi

Ubuntu 64bit

# Autori

Tym: xplagiat, xroznuk, xcopilot, xchatgpt

 - xtobol06 David Tobolik
 - xhalen00 Timotej Halenar
 - xsteti05 Jakub Stetina
 - xtesar43 Lukas Tesar

# License

Tento program je poskytovan s licenci GPLv3.
Cele zneni je v souboru LICENSE.

# Git workflow
 - main branch is protected and can be accessed only via pull requests
 - main branch **must** be compilable and functional
 - every major bug, feature or task should have its own branch
 - main features should be developed on feature branches
 - bug fixes and minor changes can be merged directly from devel branches
 - no force pushes on feature branches
 - all merges to main must have *clean* git history
 - pull requests to main are rebased

## recomended git message format
```
tag: description

details
```
 - tag
    - fix - bug fixes (both tests and production code)
    - feat - new implemented feature
    - new - new file/module
    - test - new tests
    - doc - documentation, comments
    - chore - refactoring, project restructure

 - description
    - brief description of what this commit changed
    - should not contain implementation details

 - details
    - detailed description of what was implemented and how
    - additional notes, references to issuesor other commits etc.
