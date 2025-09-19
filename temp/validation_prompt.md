# SYSTEMATIC DOCUMENTATION VALIDATION TASK

Review and validate EVERY file matching `docs/**/*.md` in the XIEITE codebase against the actual source code in include/xieite/. For each documentation file, you MUST:

1. VERIFY CODE REFERENCES
   - Check EVERY xieite:: reference exists in the actual headers
   - Validate EVERY include path (e.g., #include <xieite/category/file.hpp>)
   - Confirm EVERY function signature, template parameter, and return type
   - Test that ALL code examples would actually compile with the real headers

2. VALIDATE CLAIMS
   - Verify all numerical claims (header counts, file counts, etc.)
   - Check that described functionality matches actual implementation
   - Confirm version numbers, if any, against source
   - Validate architectural descriptions against actual code structure

3. CHECK CONSISTENCY
   - Ensure naming conventions match actual code (is_int vs is_integral, factorial as array vs function, etc.)
   - Verify that lookup tables are documented as arrays, not functions
   - Confirm return types match (e.g., minmax returns interval with .start/.end)
   - Check that all template parameter orders are correct

4. REMOVE FICTIONAL CONTENT
   - Delete any references to non-existent headers or functions
   - Remove any made-up version information if no version file exists
   - Eliminate fictional migration guides or history
   - Strip out any features that don't actually exist

5. FIX ALL ISSUES DIRECTLY
   - DO NOT create backup files
   - DO NOT ask for permission to fix
   - DO NOT pause between files
   - Edit each file directly to correct ALL issues found
   - Continue until 100% of files are validated and fixed

## VALIDATION METHOD

For each file:
1. Read the documentation file
2. Extract every code reference, include path, and technical claim
3. Verify each against the actual source using Read, Grep, and Glob tools
4. Fix all discrepancies immediately using Edit/MultiEdit
5. Move to the next file without stopping

## TRACKING

Use the TodoWrite tool to create a todo item for each file that needs validation. Mark each as completed only after ALL issues in that file are fixed.

Start with find docs -name "*.md" -type f to get the complete list, then systematically validate every single file. Do not skip any files. Do not stop until every .md file has been checked against the source code.
