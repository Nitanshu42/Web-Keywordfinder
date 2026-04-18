// ── Search state variables ─────────────────────────────
    let tokens      = [];    // all words from paragraph
    let scanIndex   = 0;     // which word we are checking RIGHT NOW
    let comparisons = 0;     // total checks made so far
    let foundCount  = 0;     // how many keywords found
    let isRunning   = false; // is auto-scan running?
    let stepMode    = false; // are we in step mode?
    let animTimer   = null;  // holds the timer so we can cancel it
    let startTime   = 0;     // to measure time taken

    // ── STEP 1: Break paragraph into words ────────────────
    // This is called "tokenizing" — splitting text into pieces
    function tokenize(text) {
      const result = [];
      // This regex splits text into: words OR non-words (spaces, punctuation)
      const regex  = /([a-zA-Z']+|[^a-zA-Z']+)/g;
      let match;
      let wordCount = 0;

      while ((match = regex.exec(text)) !== null) {
        const piece = match[0];

        if (/[a-zA-Z]/.test(piece)) {
          // This piece is a real word
          result.push({
            word:   piece,                                    // original word
            clean:  piece.replace(/[^a-zA-Z]/g,'').toLowerCase(), // cleaned for comparison
            isWord: true,
            idx:    wordCount++
          });
        } else {
          // This piece is a space or punctuation — keep it for display
          result.push({ word: piece, isWord: false });
        }
      }
      return result;
    }

    // ── STEP 2: The actual Linear Search (one word at a time) ──
    //
    // LINEAR SEARCH CONCEPT:
    // - We have an array of words: [word0, word1, word2, ...]
    // - We check EACH word one by one from index 0 to end
    // - For each word, we compare it against EVERY keyword
    // - If it matches → FOUND, if not → move to next word
    // - We NEVER skip a word. We check ALL of them.
    // This is why it is called LINEAR — it goes in a straight line.
    //
    function doStep() {

      // Skip non-word tokens (spaces, punctuation)
      while (scanIndex < tokens.length && !tokens[scanIndex].isWord) {
        scanIndex++;
      }

      // If we reached the end → search is complete
      if (scanIndex >= tokens.length) {
        finishSearch();
        return;
      }

      const token      = tokens[scanIndex];
      const kwLower    = keywords.map(function(k) { return k.toLowerCase(); });

      // ── THIS IS LINEAR SEARCH ──────────────────────────
      // Compare current word against every keyword
      comparisons += keywords.length;  // we made (keywords.length) comparisons

      const isMatch = kwLower.includes(token.clean); // check if word is a keyword
      // ──────────────────────────────────────────────────

      if (isMatch) {
        foundCount++;
      }

      // Update the counts on screen
      document.getElementById('stat-comparisons').textContent = comparisons;
      document.getElementById('stat-words').textContent       = token.idx + 1;
      document.getElementById('stat-found').textContent       = foundCount;

      // Move to next word
      scanIndex++;

      // If auto mode → schedule next step automatically
      if (isRunning && !stepMode) {
        const speed = parseInt(document.getElementById('speed-slider').value);
        animTimer   = setTimeout(doStep, speed);
      }
    }

    function finishSearch() {
      isRunning = false;
      stepMode  = false;
      const elapsed = Date.now() - startTime;
      document.getElementById('stat-time').textContent = elapsed + 'ms';
    }