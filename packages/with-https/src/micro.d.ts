import { RequestListener, IncomingMessage, ServerResponse } from 'http'

export type RequestHandler = (req: IncomingMessage, res: ServerResponse) => any
declare function serve(fn: RequestHandler): RequestListener

declare function run(req: IncomingMessage, res: ServerResponse, fn: RequestHandler): Promise<void>
declare function json(req: IncomingMessage, info?: { limit?: string | number, encoding?: string }): Promise<any>
declare function text(req: IncomingMessage, info?: { limit?: string | number, encoding?: string }): Promise<string>
declare function buffer(req: IncomingMessage, info?: { limit?: string | number, encoding?: string }): Promise<Buffer | string>
declare function send(res: ServerResponse, code: number, data?: any): Promise<void>
declare function createError(code: number, msg: string, orig?: Error): Error & { statusCode: number, originalError?: Error }
declare function sendError(req: IncomingMessage, res: ServerResponse, info: { statusCode?: number, status?: number, message?: string, stack?: string }): Promise<void>
export default serve
