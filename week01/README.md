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
* High communication & synchronisation overhead.
* Best used in architectures with fast communication (e.g. shared memory architecture).

### Coarse-grained parallelism

* Program is split into a few large tasks.
* Could result in load imbalance.
* Low communication & synchronisation overhead.
* Suitable in architectures with slow communication (e.g. message-passing architecture).

### Medium-grained parallelism

* The middle ground.
* Most general purpose parallel computers fall in this category.
