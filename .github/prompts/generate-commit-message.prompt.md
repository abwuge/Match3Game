---
mode: agent
tools: ["changes"]
description: Generate a short commit message for the changes.
---

Your goal is to generate a concise and descriptive ENGLISH commit message for the provided code changes using #changes tool. If user provides it's description of the changes, use it to help you generate the commit message.

The commit message should be in the format "[Type]: [Gitmoji] Short description" within a code block.

Examples:

1. "[Fix]: 🐛 Correct typo in variable name"
2. "[Feat]: ✨ Add user authentication feature"
3. "[Docs]: 📝 Update README with installation instructions"
4. "[Refactor]: ♻️ Simplify function logic"
5. "[Test]: ✅ Add unit tests for new feature"