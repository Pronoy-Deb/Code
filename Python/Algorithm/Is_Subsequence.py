# Complexity: O(main.size())

# For String:
# Iterative Approach:

def sseq(main, sub):
    m, n, i, j = len(main), len(sub), 0, 0
    while i < m and j < n:
        if main[i] == sub[j]: j += 1
        i += 1
    return j == n

# Recursive Approach:

def sseq(main, sub, m_sz = None, s_sz = None):
    if m_sz is None and s_sz is None:
        m_sz, s_sz = len(main), len(sub)
    if not s_sz: return True
    if not m_sz: return False
    if main[m_sz - 1] == sub[s_sz - 1]:
        return sseq(main, sub, m_sz - 1, s_sz - 1)
    return sseq(main, sub, m_sz - 1, s_sz)

# For Vector:
# Iterative Approach:

def sseq(main, sub):
    m, n, i, j = len(main), len(sub), 0, 0
    while i < m and j < n:
        if main[i] == sub[j]: j += 1
        i += 1
    return j == n

# Recursive Approach:

def sseq(main, sub, m_sz = None, s_sz = None):
    if m_sz is None and s_sz is None:
        m_sz, s_sz = len(main), len(sub)
    if not s_sz: return True
    if not m_sz: return False
    if main[m_sz - 1] == sub[s_sz - 1]:
        return sseq(main, sub, m_sz - 1, s_sz - 1)
    return sseq(main, sub, m_sz - 1, s_sz)