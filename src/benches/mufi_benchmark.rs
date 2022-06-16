use criterion::{black_box, criterion_group, criterion_main, Criterion};
use mufi_bench::compile;

pub fn bench(c: &mut Criterion){
    c.bench_function("The Fibonacci Benchmark", |b| b.iter(|| compile(black_box("/hdd/mufic/src/test/fibonacci.mufi"))));
}

criterion_group!(benches, bench);
criterion_main!(benches);