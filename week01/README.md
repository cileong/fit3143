# Week 1: Introduction to parallel computing & distributed systems

Types of parallelism

* Bit-level parallelism
* Instruction-level parallelism (ILP)
* Data-level parallelism (DLP)
* Task parallelism
* Job-level parallelism

## Flynn's Taxonomy

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
