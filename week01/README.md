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
