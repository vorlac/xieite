#!/bin/bash
# Build and deploy mdBook to gh-pages branch

# Build the book
cd docs
mdbook build
cd ..

# Create a temporary directory
tmp_dir=$(mktemp -d)
cp -r docs/book/* "$tmp_dir"

# Switch to gh-pages branch
git checkout gh-pages || git checkout -b gh-pages

# Clear old content and copy new
rm -rf *
cp -r "$tmp_dir"/* .

# Add .nojekyll to prevent Jekyll processing
touch .nojekyll

# Commit and push
git add .
git commit -m "Deploy mdBook documentation"
git push origin gh-pages

# Switch back to main branch
git checkout main

# Clean up
rm -rf "$tmp_dir"

echo "Documentation deployed to GitHub Pages!"
echo "Visit: https://vorlac.github.io/xieite/"
