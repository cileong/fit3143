# Week 1: Introduction to parallel computing & distributed systems

## Bottlenecks of serial computing (research)

### Memory wall

* Increasing operating frequency will not optimize the performance.
* Bottleneck: gap between CPU and memory throughput.

### ILP wall

* Difficulty in full parallel instruction processing.

### Power wall

* Power consumption doubled following the doubling of operating frequency.
* 1% clock increase = 3% power increase.

## Levels of parallelism

### Bit-level parallelism

* Increase processor word size.
* Reduces number of instructions needed to perform operations on variables of sizes > word length.
* Example: 8-bit processors need 2 instructions to add two 16-bit integers; 16-bit processors only need 1.

### Instruction-level parallelism (ILP) (research)

* Superscalar processor with multiple executing units and out-of-order (dynamic) execution.

### Data-level parallelism (DLP)

* Data is split into multiple chunks.
* Each processor operates on a chunk.
* All processors carry out the same task.

### Task parallelism

* Each processor executes a different thread/process on the data.

## Flynn's taxonomy

Classifies architectures based on the number of concurrent *instruction* and *data* streams available.

### SISD

* Single *instruction* (SI) stream, single *data* (SD) stream.
* SI: one instruction stream being acted on by CPU / clock cycle.
* SD: one data stream as input / clock cycle.
* Serial & deterministic execution.

### SIMD

* Single *instruction* (SI) stream, multiple *data* (MD) streams.
* SI: all processing units execute the same instruction at any given clock cycle.
* MD: each processing unit operates on a different data element.
* Synchronous (lockstep) & deterministic execution.

## Granularity

If $T_\text{comp}$ denotes the computation time, $T_\text{comm}$ denotes the communication time, then the granularity (or grain size), $G$ of a task is given by:

$$
    G = \frac{T_\text{comp}}{T_\text{comm}}
$$

## Types of parallelism

### Fine-grained parallelism

* Program is broken down to a lot of small tasks.
* Facilitates load balancing.
* High communication & synchronization overhead.
* Best used in architectures with fast communication (e.g. shared memory architecture).

### Coarse-grained parallelism

* Program is split into a few large tasks.
* Could result in load imbalance.
* Low communication & synchronization overhead.
* Suitable in architectures with slow communication (e.g. message-passing architecture).

### Medium-grained parallelism

* The middle ground.
* Most general purpose parallel computers fall in this category.

## Speedup

The measure of relative performance between a single processor system and a multiprocessor system with $n$ processors, $S(n)$ is given by:

$$
    S(n) = \frac{\text{Execution time with 1 processor}}{\text{Execution time with $n$ processors}} = \frac{T_1}{T_n}
$$

### Theoretical speedup

Let $r_\text{serial}$ be the ratio of time that is executed serially, $T_\text{serial}$ and $T_\text{parallel}$ be the time required to solve a given task serially and in parallel with $n$ processors respectively, then the theoretical speedup $S(n)$ is given by:

$$
\begin{align*}
    S(n) &= \frac{T_\text{serial}}{T_\text{parallel}} \\
    &= \frac{T_\text{serial}}{r_\text{serial} \cdot T_\text{serial} + (1 - r_\text{serial}) \cdot \frac{T_\text{serial}}{n}} \\
    &= \frac{1}{r_\text{serial} + (1 - r_\text{serial}) \cdot \frac{1}{n}} \\
    &= \frac{n}{1 + r_\text{serial}(n-1)}
\end{align*}
$$

### Maximum speedup

The maximum speedup is observed when the task can be run entirely in parallel, i.e. $r_\text{serial} = 0$:

$$
    S(n) = \frac{n}{1 + 0(n-1)} = n
$$

$\therefore$ Maximum achievable speedup is $S(n) = n$, and normally $S(n) \le n$.

#### Superlinear speedup $S(n) > n$

Usually due to:

* Suboptimal sequential algorithm.
* Architecture favors parallel formation.
* Extra memory in multiprocessor system, which can hold more of the problem data at any instant, leading to relatively faster disk-memory traffic.
