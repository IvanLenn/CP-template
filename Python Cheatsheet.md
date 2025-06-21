## Data structure

- list
  - `a.sort()` sorts a list

```python
b = set(B)
any(x in b for x in A) # Check if list A and B have elements in common
```

- deque
  - Use it as stack / queue is good enough.

```python
q = collections.deque()
q.append(x)   	# Append x to the tail
q.appendleft(x) # Append x to the head
q.pop()
q.popleft()
```

- Stack
  - Can use a deque instead

```python
st = []
st.append()
st.pop()
```

- set
  - Unordered.


```python
st = set()
st.add(1)
st.discard(2) # st.remove(2) will error if not 2 in st
1 in st
```

- SortedList
  - It's a multiset.


```python
st = sortedcontainers.SortedList()
st.add((1, 1))											
assert(st[0][0] == 1) 												# Support indexing
st.remove((1, 1))															# Only remove the first occurence of (1, 1)
del st[st.bisect_left((1, 1)):st.bisect_right((1, 1))] 	# Deletes all occurences of (1, 1)
```

- OrderedDict

```python
c = collections.Ordereddict()
c.move_to_end(key, last = True) # last meams RHS of deque
c.popitem(last = True) 				  # LIFO order
val = c.pop(key)				
```

- Slicing

```python
a[:] 							# Full shallow copy (outer list is new, nested objects remain shared)
a[start:stop]  		# Half-open interval
a[::-2] 				  # Reverse direction, step of 2
```

- Tuple vs. List
  - List is: mutable, uses [], not hashable, larger memory...
  - Tuple: when the content is constant / a hashable key

- defaultdict

```python
dt = collections.defaultdict(list) # dict mapping from hashable types -> list
dt[key] = val 										 # Add keys
dt.pop(key)												 # Remove keys; errors if key is not present
print(mp.keys(), mp.values())
```



## MISC

- String
  - Int to string: `str(i)`
  - Append to string: `s += 'random'`
  - `ord('a') = 97`, `chr(97) = 'a'` 
  - `sorted(s)` returns a list of singleton strings
  - `str.split(",")` will split by '.'. `str.split(r"[:,.]")` will split by everything inside
- Function capture
  - read-only use -> captures the value from the nearest enclosing scope
  - Any assignment -> local binding
  - Override with nonlocal to rebind the variable from the nearest enclosing

Bitwise operator: `&, |, ^, ~, <<, >>`

Logical operator: `and, or, not`

Use `math.inf` as equvalent of `IntMax` in C++

`int(a / b)` truncates toward 0

`random.randint(a, b)` returns uniform int in `[a, b]`

`x = y`  is testing object identity. `=` is testing value equality

`bisect_left(a, x)`  will return the first index of the element in `a` that is `>= x`, similar to `lower_bound` in C++; `bisect_right(a, x)` is similar to `upper_bound` in C++

`=` always binds a new name to the same object. `.copy()` will duplicate the container but reuse the underlying elements.

```python
B = [1, 2]
A = B
A.append(3) 								# B = [1, 2, 3]

D = {'a' = [1], 'b' = [1]}
C = D
C['a'].append(2) 						# D['a'] = [1, 2] becuase of shared inner object
C['a'] = [2]								# D['a'] = [1, 2] because rebind of list

F = {(1, 2), (3, 4)}
E = F
E.add((5, 6)) 							# F = {(1, 2), (3, 4)} because tuples are immutable

H = [[1, 2], [3, 4]]
G = [inn[:] for inn in H] 	# G is new. inn[:] creates one new list object, filled with the same element references that were in inn.
```



Remaining problems: 642, 332, 126 - 269, 4 - 123s
