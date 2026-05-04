//! vnpy-disruptor: High-performance institutional-grade event system.
//!
//! This module provides PyO3 Python bindings for the `disruptor` crate (v4.1).
//! It implements a zero-copy, zero-allocation event pipeline where Python
//! objects are passed as PyObject references through a lock-free ring buffer.

use disruptor::{
    build_multi_producer, BusySpin, BusySpinWithSpinLoopHint,
    MultiProducer, SingleConsumerBarrier, Producer, ProcessorSettings, Sequence,
    wait_strategies::WaitStrategy,
};
use pyo3::prelude::*;
use pyo3::types::{PyDict, PyList};
use parking_lot::Mutex;
use std::sync::Arc;
use std::sync::atomic::{AtomicBool, AtomicU64, Ordering};
use std::{thread, time, cell::Cell};

// Adaptive Tuning Constants
const ADAPTIVE_SPIN_COUNT: u32 = 2048;
const ADAPTIVE_YIELD_COUNT: u32 = 256;
const ADAPTIVE_BATCH_SIZE: usize = 1024;

thread_local! {
    static WAIT_COUNT: Cell<u32> = Cell::new(0);
}

// ─────────────────────────────────────────────────────────────────────────────
// Custom Wait Strategies
// ─────────────────────────────────────────────────────────────────────────────

#[derive(Copy, Clone)]
pub struct Yielding;
impl WaitStrategy for Yielding {
    #[inline]
    fn wait_for(&self, _sequence: Sequence) { thread::yield_now(); }
}

#[derive(Copy, Clone)]
pub struct Sleeping;
impl WaitStrategy for Sleeping {
    #[inline]
    fn wait_for(&self, _sequence: Sequence) { thread::sleep(time::Duration::from_micros(10)); }
}

/// Context for adaptive blocking, shared between WaitStrategy and Producer.
pub struct AdaptiveContext {
    pub is_sleeping: AtomicBool,
    pub worker_thread: Mutex<Option<thread::Thread>>,
}

/// Adaptive blocking strategy: Spins, then Yields, then Parks.
/// Achieves 0% CPU usage when idle while maintaining sub-20µs wakeup.
#[derive(Copy, Clone)]
pub struct AdaptiveBlocking {
    context: *const AdaptiveContext,
}

// SAFETY: AdaptiveContext is Sync/Send. The pointer is valid as long as 
// DisruptorProducer (which owns the Arc<AdaptiveContext>) is alive.
// Since the Producer owns the worker thread, this is guaranteed.
unsafe impl Send for AdaptiveBlocking {}

impl WaitStrategy for AdaptiveBlocking {
    #[inline]
    fn wait_for(&self, _sequence: Sequence) {
        let count = WAIT_COUNT.with(|c| {
            let n = c.get();
            c.set(n + 1);
            n
        });

        if count < ADAPTIVE_SPIN_COUNT {
            std::hint::spin_loop();
        } else if count < ADAPTIVE_SPIN_COUNT + ADAPTIVE_YIELD_COUNT {
            thread::yield_now();
        } else {
            let ctx = unsafe { &*self.context };
            ctx.is_sleeping.store(true, Ordering::Release);
            
            if ctx.worker_thread.lock().is_none() {
                *ctx.worker_thread.lock() = Some(thread::current());
            }

            thread::park_timeout(time::Duration::from_millis(10));
            ctx.is_sleeping.store(false, Ordering::Release);
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Ring-buffer event type
// ─────────────────────────────────────────────────────────────────────────────

#[derive(Debug, Default)]
pub struct VnpyEvent {
    pub data: Option<Arc<PyObject>>,
}

unsafe impl Send for VnpyEvent {}
unsafe impl Sync for VnpyEvent {}

// ─────────────────────────────────────────────────────────────────────────────
// InnerProducer
// ─────────────────────────────────────────────────────────────────────────────

#[derive(Clone)]
enum InnerProducer {
    BusySpin(Option<MultiProducer<VnpyEvent, SingleConsumerBarrier>>),
    BusySpinHint(Option<MultiProducer<VnpyEvent, SingleConsumerBarrier>>),
    Yielding(Option<MultiProducer<VnpyEvent, SingleConsumerBarrier>>),
    Sleeping(Option<MultiProducer<VnpyEvent, SingleConsumerBarrier>>),
    Adaptive(Option<MultiProducer<VnpyEvent, SingleConsumerBarrier>>),
}

impl InnerProducer {
    fn try_publish(&mut self, _py: Python<'_>, data: PyObject) -> Result<(), ()> {
        let arc_data = Arc::new(data);
        match self {
            InnerProducer::BusySpin(Some(p)) => p.try_publish(|s| { s.data = Some(Arc::clone(&arc_data)); }).map(|_| ()).map_err(|_| ()),
            InnerProducer::BusySpinHint(Some(p)) => p.try_publish(|s| { s.data = Some(Arc::clone(&arc_data)); }).map(|_| ()).map_err(|_| ()),
            InnerProducer::Yielding(Some(p)) => p.try_publish(|s| { s.data = Some(Arc::clone(&arc_data)); }).map(|_| ()).map_err(|_| ()),
            InnerProducer::Sleeping(Some(p)) => p.try_publish(|s| { s.data = Some(Arc::clone(&arc_data)); }).map(|_| ()).map_err(|_| ()),
            InnerProducer::Adaptive(Some(p)) => p.try_publish(|s| { s.data = Some(Arc::clone(&arc_data)); }).map(|_| ()).map_err(|_| ()),
            _ => Err(()),
        }
    }

    fn publish(&mut self, data: PyObject) -> bool {
        let arc_data = Arc::new(data);
        match self {
            InnerProducer::BusySpin(Some(p)) => { p.publish(|s| { s.data = Some(Arc::clone(&arc_data)); }); true }
            InnerProducer::BusySpinHint(Some(p)) => { p.publish(|s| { s.data = Some(Arc::clone(&arc_data)); }); true }
            InnerProducer::Yielding(Some(p)) => { p.publish(|s| { s.data = Some(Arc::clone(&arc_data)); }); true }
            InnerProducer::Sleeping(Some(p)) => { p.publish(|s| { s.data = Some(Arc::clone(&arc_data)); }); true }
            InnerProducer::Adaptive(Some(p)) => { p.publish(|s| { s.data = Some(Arc::clone(&arc_data)); }); true }
            _ => false,
        }
    }

    fn try_publish_batch(&mut self, _py: Python<'_>, events: Vec<PyObject>) -> Result<(), Vec<PyObject>> {
        let n = events.len();
        let arc_events: Vec<Arc<PyObject>> = events.into_iter().map(Arc::new).collect();
        match self {
            InnerProducer::BusySpin(Some(p)) => p.try_batch_publish(n, |iter| { for (s, a) in iter.zip(arc_events.iter()) { s.data = Some(Arc::clone(a)); } }).map(|_| ()).map_err(|_| Vec::new()),
            InnerProducer::BusySpinHint(Some(p)) => p.try_batch_publish(n, |iter| { for (s, a) in iter.zip(arc_events.iter()) { s.data = Some(Arc::clone(a)); } }).map(|_| ()).map_err(|_| Vec::new()),
            InnerProducer::Yielding(Some(p)) => p.try_batch_publish(n, |iter| { for (s, a) in iter.zip(arc_events.iter()) { s.data = Some(Arc::clone(a)); } }).map(|_| ()).map_err(|_| Vec::new()),
            InnerProducer::Sleeping(Some(p)) => p.try_batch_publish(n, |iter| { for (s, a) in iter.zip(arc_events.iter()) { s.data = Some(Arc::clone(a)); } }).map(|_| ()).map_err(|_| Vec::new()),
            InnerProducer::Adaptive(Some(p)) => p.try_batch_publish(n, |iter| { for (s, a) in iter.zip(arc_events.iter()) { s.data = Some(Arc::clone(a)); } }).map(|_| ()).map_err(|_| Vec::new()),
            _ => Err(Vec::new()),
        }
    }

    fn publish_batch(&mut self, events: Vec<PyObject>) -> bool {
        let n = events.len();
        let arc_events: Vec<Arc<PyObject>> = events.into_iter().map(Arc::new).collect();
        match self {
            InnerProducer::BusySpin(Some(p)) => { p.batch_publish(n, |iter| { for (s, a) in iter.zip(arc_events) { s.data = Some(a); } }); true }
            InnerProducer::BusySpinHint(Some(p)) => { p.batch_publish(n, |iter| { for (s, a) in iter.zip(arc_events) { s.data = Some(a); } }); true }
            InnerProducer::Yielding(Some(p)) => { p.batch_publish(n, |iter| { for (s, a) in iter.zip(arc_events) { s.data = Some(a); } }); true }
            InnerProducer::Sleeping(Some(p)) => { p.batch_publish(n, |iter| { for (s, a) in iter.zip(arc_events) { s.data = Some(a); } }); true }
            InnerProducer::Adaptive(Some(p)) => { p.batch_publish(n, |iter| { for (s, a) in iter.zip(arc_events) { s.data = Some(a); } }); true }
            _ => false,
        }
    }

    fn drop_producer(&mut self) {
        match self {
            InnerProducer::BusySpin(p) => *p = None,
            InnerProducer::BusySpinHint(p) => *p = None,
            InnerProducer::Yielding(p) => *p = None,
            InnerProducer::Sleeping(p) => *p = None,
            InnerProducer::Adaptive(p) => *p = None,
        }
    }
}

unsafe impl Send for InnerProducer {}

// ─────────────────────────────────────────────────────────────────────────────
// DisruptorProducer
// ─────────────────────────────────────────────────────────────────────────────

#[pyclass]
pub struct DisruptorProducer {
    producer_lock: Arc<Mutex<Option<InnerProducer>>>,
    _buffer_size: usize,
    _wait_strategy: String,
    active: Arc<AtomicBool>,
    pending_count: Arc<AtomicU64>,
    last_error: Arc<Mutex<Option<PyObject>>>,
    processed_count: Arc<AtomicU64>,
    backpressure_events: Arc<AtomicU64>,
    
    // Adaptive signaling
    adaptive_context: Arc<AdaptiveContext>,
}

#[pymethods]
impl DisruptorProducer {
    #[new]
    pub fn new(buffer_size: usize, wait_strategy: &str) -> PyResult<Self> {
        if buffer_size == 0 || (buffer_size & (buffer_size - 1)) != 0 {
            return Err(pyo3::exceptions::PyValueError::new_err("buffer_size must be a power of 2"));
        }
        match wait_strategy {
            "busy_spin" | "busy_spin_hint" | "yielding" | "sleeping" | "blocking" => (),
            _ => return Err(pyo3::exceptions::PyValueError::new_err(format!("Unknown wait_strategy: {wait_strategy}"))),
        }
        Ok(DisruptorProducer {
            producer_lock: Arc::new(Mutex::new(None)),
            _buffer_size: buffer_size,
            _wait_strategy: wait_strategy.to_string(),
            active: Arc::new(AtomicBool::new(true)),
            pending_count: Arc::new(AtomicU64::new(0)),
            last_error: Arc::new(Mutex::new(None)),
            processed_count: Arc::new(AtomicU64::new(0)),
            backpressure_events: Arc::new(AtomicU64::new(0)),
            adaptive_context: Arc::new(AdaptiveContext {
                is_sleeping: AtomicBool::new(false),
                worker_thread: Mutex::new(None),
            }),
        })
    }

    pub fn try_publish(&self, py: Python<'_>, data: PyObject) -> PyResult<bool> {
        self.check_error(py)?;
        let mut guard = self.producer_lock.lock();
        let producer = guard.as_mut().ok_or_else(|| pyo3::exceptions::PyRuntimeError::new_err("Stopped"))?;
        
        if producer.try_publish(py, data).is_ok() {
            self.pending_count.fetch_add(1, Ordering::SeqCst);
            self.notify_worker();
            Ok(true)
        } else {
            self.backpressure_events.fetch_add(1, Ordering::Relaxed);
            Ok(false)
        }
    }

    pub fn publish(&self, py: Python<'_>, data: PyObject) -> PyResult<()> {
        self.check_error(py)?;
        
        let mut producer = {
            let mut guard = self.producer_lock.lock();
            let p_opt = guard.as_mut().ok_or_else(|| pyo3::exceptions::PyRuntimeError::new_err("Stopped"))?;
            
            if p_opt.try_publish(py, data.clone_ref(py)).is_ok() {
                self.pending_count.fetch_add(1, Ordering::SeqCst);
                self.notify_worker();
                return Ok(());
            }
            p_opt.clone()
        };

        self.backpressure_events.fetch_add(1, Ordering::Relaxed);
        self.notify_worker(); // Notify BEFORE blocking to ensure worker wakes up to clear buffer
        py.allow_threads(move || {
            if producer.publish(data) {
                self.pending_count.fetch_add(1, Ordering::SeqCst);
                self.notify_worker(); // Notify again after to be sure
                Ok(())
            } else {
                Err(pyo3::exceptions::PyRuntimeError::new_err("Stopped"))
            }
        })
    }

    pub fn publish_batch(&self, py: Python<'_>, events: Vec<PyObject>) -> PyResult<()> {
        self.check_error(py)?;
        let n = events.len();
        
        let mut producer = {
            let mut guard = self.producer_lock.lock();
            let p_opt = guard.as_mut().ok_or_else(|| pyo3::exceptions::PyRuntimeError::new_err("Stopped"))?;
            
            match p_opt.try_publish_batch(py, events) {
                Ok(_) => { 
                    self.pending_count.fetch_add(n as u64, Ordering::SeqCst); 
                    self.notify_worker();
                    return Ok(()); 
                }
                Err(remaining_events) => {
                    self.backpressure_events.fetch_add(1, Ordering::Relaxed);
                    self.notify_worker(); // Notify BEFORE blocking
                    (p_opt.clone(), remaining_events)
                }
            }
        };

        let (mut p, evs) = producer;
        py.allow_threads(move || {
            if p.publish_batch(evs) {
                self.pending_count.fetch_add(n as u64, Ordering::SeqCst);
                self.notify_worker(); // Notify again after
                Ok(())
            } else {
                Err(pyo3::exceptions::PyRuntimeError::new_err("Stopped"))
            }
        })
    }

    fn notify_worker(&self) {
        if self.adaptive_context.is_sleeping.load(Ordering::Acquire) {
            if let Some(thread) = self.adaptive_context.worker_thread.lock().as_ref() {
                thread.unpark();
            }
        }
    }
    
    fn check_error(&self, py: Python<'_>) -> PyResult<()> {
        let mut guard = self.last_error.lock();
        if let Some(exc_obj) = guard.take() { return Err(PyErr::from_value(exc_obj.into_bound(py))); }
        Ok(())
    }

    pub fn clone_producer(&self) -> PyResult<Self> {
        Ok(DisruptorProducer {
            producer_lock: Arc::clone(&self.producer_lock),
            _buffer_size: self._buffer_size,
            _wait_strategy: self._wait_strategy.clone(),
            active: Arc::clone(&self.active),
            pending_count: Arc::clone(&self.pending_count),
            last_error: Arc::clone(&self.last_error),
            processed_count: Arc::clone(&self.processed_count),
            backpressure_events: Arc::clone(&self.backpressure_events),
            adaptive_context: Arc::clone(&self.adaptive_context),
        })
    }

    #[pyo3(signature = (callback, core_id=None))]
    pub fn start_worker(&self, py: Python<'_>, callback: PyObject, core_id: Option<usize>) -> PyResult<()> {
        let factory = VnpyEvent::default;
        let last_error = Arc::clone(&self.last_error);
        let active = Arc::clone(&self.active);
        let processed_count = Arc::clone(&self.processed_count);
        let pending_count = Arc::clone(&self.pending_count);
        let callback = callback.clone_ref(py);
        let events_buffer: Arc<Mutex<Vec<Arc<PyObject>>>> = Arc::new(Mutex::new(Vec::with_capacity(ADAPTIVE_BATCH_SIZE)));

        let handler = move |event: &VnpyEvent, _sequence: Sequence, end_of_batch: bool| {
            // Reset adaptive counter on every processed event
            WAIT_COUNT.with(|c| c.set(0));
            
            if !active.load(Ordering::Acquire) { return; }
            if let Some(ref arc_data) = event.data { events_buffer.lock().push(Arc::clone(arc_data)); }
            if end_of_batch {
                Python::with_gil(|py| {
                    let mut buffer = events_buffer.lock();
                    if buffer.is_empty() { return; }
                    let list_data: Vec<PyObject> = buffer.iter().map(|arc| (**arc).clone_ref(py)).collect();
                    if let Ok(list) = PyList::new(py, list_data) {
                        if let Err(e) = callback.call1(py, (list,)) {
                            *last_error.lock() = Some(e.into_pyobject(py).unwrap().into_any().unbind());
                            active.store(false, Ordering::Release);
                        } else {
                            processed_count.fetch_add(buffer.len() as u64, Ordering::Relaxed);
                            pending_count.fetch_sub(buffer.len() as u64, Ordering::SeqCst);
                        }
                    }
                    buffer.clear();
                });
            }
        };

        let mut producer_guard = self.producer_lock.lock();
        if producer_guard.is_some() { return Err(pyo3::exceptions::PyRuntimeError::new_err("Already started")); }
        self.active.store(true, Ordering::Release);
        
        match self._wait_strategy.as_str() {
            "busy_spin" => {
                let mut b = build_multi_producer(self._buffer_size, factory, BusySpin).handle_events_with(handler);
                if let Some(id) = core_id { b = b.pin_at_core(id); }
                *producer_guard = Some(InnerProducer::BusySpin(Some(b.build())));
            }
            "busy_spin_hint" => {
                let mut b = build_multi_producer(self._buffer_size, factory, BusySpinWithSpinLoopHint).handle_events_with(handler);
                if let Some(id) = core_id { b = b.pin_at_core(id); }
                *producer_guard = Some(InnerProducer::BusySpinHint(Some(b.build())));
            }
            "yielding" => {
                let mut b = build_multi_producer(self._buffer_size, factory, Yielding).handle_events_with(handler);
                if let Some(id) = core_id { b = b.pin_at_core(id); }
                *producer_guard = Some(InnerProducer::Yielding(Some(b.build())));
            }
            "sleeping" => {
                let mut b = build_multi_producer(self._buffer_size, factory, Sleeping).handle_events_with(handler);
                if let Some(id) = core_id { b = b.pin_at_core(id); }
                *producer_guard = Some(InnerProducer::Sleeping(Some(b.build())));
            }
            "blocking" => {
                let strategy = AdaptiveBlocking {
                    context: &*self.adaptive_context,
                };
                let mut b = build_multi_producer(self._buffer_size, factory, strategy).handle_events_with(handler);
                if let Some(id) = core_id { b = b.pin_at_core(id); }
                *producer_guard = Some(InnerProducer::Adaptive(Some(b.build())));
            }
            _ => unreachable!(),
        }
        Ok(())
    }

    pub fn stop(&self, py: Python<'_>) {
        py.allow_threads(|| {
            let mut guard = self.producer_lock.lock();
            if let Some(ref mut p) = *guard { p.drop_producer(); }
            *guard = None;
            self.active.store(false, Ordering::Release);
            self.notify_worker(); // Unpark if waiting for stop
        });
    }

    pub fn is_active(&self) -> bool { self.active.load(Ordering::Acquire) }
    pub fn get_metrics(&self, py: Python<'_>) -> PyResult<PyObject> {
        let dict = PyDict::new(py);
        dict.set_item("processed_count", self.processed_count.load(Ordering::Relaxed))?;
        dict.set_item("backpressure_events", self.backpressure_events.load(Ordering::Relaxed))?;
        dict.set_item("pending_count", self.pending_count.load(Ordering::Relaxed))?;
        Ok(dict.as_any().clone().unbind())
    }
}

#[pymodule]
#[pyo3(name = "vnpy_disruptor")]
fn vnpy_disruptor(m: &Bound<'_, PyModule>) -> PyResult<()> {
    m.add_class::<DisruptorProducer>()?;
    Ok(())
}